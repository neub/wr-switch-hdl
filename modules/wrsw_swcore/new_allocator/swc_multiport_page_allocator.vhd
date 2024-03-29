-------------------------------------------------------------------------------
-- Title      : multiport page allocator
-- Project    : WhiteRabbit switch
-------------------------------------------------------------------------------
-- File       : swc_multiport_page_allocator.vhd
-- Author     : Tomasz Wlostowski
-- Company    : CERN BE-Co-HT
-- Created    : 2010-04-08
-- Last update: 2012-03-15
-- Platform   : FPGA-generic
-- Standard   : VHDL'87
-------------------------------------------------------------------------------
-- Description: 
-------------------------------------------------------------------------------
--
-- Copyright (c) 2010 Tomasz Wlostowski, Maciej Lipinski / CERN
--
-- This source file is free software; you can redistribute it   
-- and/or modify it under the terms of the GNU Lesser General   
-- Public License as published by the Free Software Foundation; 
-- either version 2.1 of the License, or (at your option) any   
-- later version.                                               
--
-- This source is distributed in the hope that it will be       
-- useful, but WITHOUT ANY WARRANTY; without even the implied   
-- warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR      
-- PURPOSE.  See the GNU Lesser General Public License for more 
-- details.                                                     
--
-- You should have received a copy of the GNU Lesser General    
-- Public License along with this source; if not, download it   
-- from http://www.gnu.org/licenses/lgpl-2.1.html
--
-------------------------------------------------------------------------------
-- Revisions  :
-- Date        Version  Author   Description
-- 2010-04-08  1.0      twlostow Created
-- 2010-10-11  1.1      mlipinsk comments added !!!!!
-- 2010-10-11  1.1      twlostow changed allocator
-- 2012-02-02  2.0      mlipinsk generic-azed
-------------------------------------------------------------------------------


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.swc_swcore_pkg.all;
use work.genram_pkg.all;
use work.gencores_pkg.all;

entity swc_multiport_page_allocator is
  generic (
    g_page_addr_width : integer := 10;    --:= c_swc_page_addr_width;
    g_num_ports       : integer := 7;     --:= c_swc_num_ports
    g_page_num        : integer := 1024;  --:= c_swc_packet_mem_num_pages
    g_usecount_width  : integer := 3      --:= c_swc_usecount_width
    );
  port (
    rst_n_i : in std_logic;
    clk_i   : in std_logic;

    alloc_i      : in std_logic_vector(g_num_ports - 1 downto 0);
    free_i       : in std_logic_vector(g_num_ports - 1 downto 0);
    force_free_i : in std_logic_vector(g_num_ports - 1 downto 0);
    set_usecnt_i : in std_logic_vector(g_num_ports - 1 downto 0);

    alloc_done_o      : out std_logic_vector(g_num_ports - 1 downto 0);
    free_done_o       : out std_logic_vector(g_num_ports - 1 downto 0);
    force_free_done_o : out std_logic_vector(g_num_ports - 1 downto 0);
    set_usecnt_done_o : out std_logic_vector(g_num_ports - 1 downto 0);


    pgaddr_free_i       : in std_logic_vector(g_num_ports * g_page_addr_width - 1 downto 0);
    pgaddr_force_free_i : in std_logic_vector(g_num_ports * g_page_addr_width - 1 downto 0);
    pgaddr_usecnt_i     : in std_logic_vector(g_num_ports * g_page_addr_width - 1 downto 0);

    usecnt_i       : in  std_logic_vector(g_num_ports * g_usecount_width - 1 downto 0);
    pgaddr_alloc_o : out std_logic_vector(g_page_addr_width-1 downto 0);

    free_last_usecnt_o : out std_logic_vector(g_num_ports - 1 downto 0);

    nomem_o : out std_logic;

    tap_out_o : out std_logic_vector(62 + 49 downto 0)
    );

end swc_multiport_page_allocator;

architecture syn of swc_multiport_page_allocator is


  component swc_page_allocator_new
    generic (
      g_num_pages       : integer;
      g_page_addr_width : integer;
      g_num_ports       : integer;
      g_usecount_width  : integer);
    port (
      clk_i                   : in  std_logic;
      rst_n_i                 : in  std_logic;
      alloc_i                 : in  std_logic;
      free_i                  : in  std_logic;
      force_free_i            : in  std_logic;
      set_usecnt_i            : in  std_logic;
      usecnt_i                : in  std_logic_vector(g_usecount_width-1 downto 0);
      pgaddr_i                : in  std_logic_vector(g_page_addr_width -1 downto 0);
      pgaddr_o                : out std_logic_vector(g_page_addr_width -1 downto 0);
      free_last_usecnt_o      : out std_logic;
      done_o                  : out std_logic;
      nomem_o                 : out std_logic;
      dbg_double_free_o       : out std_logic;
      dbg_double_force_free_o : out std_logic;
      dbg_q_write_o           : out std_logic;
      dbg_q_read_o            : out std_logic;
      dbg_initializing_o      : out std_logic);
  end component;

  type t_port_state is record
    req_ib         : std_logic;
    req_ob         : std_logic;
    req_alloc      : std_logic;
    req_free       : std_logic;
    req_set_usecnt : std_logic;
    req_force_free : std_logic;

    grant_ib_d : std_logic_vector(2 downto 0);
    grant_ob_d : std_logic_vector(2 downto 0);

    done_alloc      : std_logic;
    done_free       : std_logic;
    done_set_usecnt : std_logic;
    done_force_free : std_logic;
  end record;

  type t_port_state_array is array(0 to g_num_ports-1) of t_port_state;

  signal ports              : t_port_state_array;
  signal arb_req, arb_grant : std_logic_vector(2*g_num_ports-1 downto 0);


  signal pg_alloc            : std_logic;
  signal pg_free             : std_logic;
  signal pg_force_free       : std_logic;
  signal pg_set_usecnt       : std_logic;
  signal pg_usecnt           : std_logic_vector(g_usecount_width-1 downto 0);
  signal pg_addr             : std_logic_vector(g_page_addr_width -1 downto 0);
  signal pg_addr_alloc       : std_logic_vector(g_page_addr_width -1 downto 0);
  signal pg_free_last_usecnt : std_logic;
  signal pg_done             : std_logic;
  signal pg_nomem            : std_logic;

  signal alloc_done      : std_logic_vector(g_num_ports - 1 downto 0);
  signal free_done       : std_logic_vector(g_num_ports - 1 downto 0);
  signal force_free_done : std_logic_vector(g_num_ports - 1 downto 0);
  signal set_usecnt_done : std_logic_vector(g_num_ports - 1 downto 0);

  signal dbg_double_force_free, dbg_double_free    : std_logic;
  signal dbg_q_read, dbg_q_write, dbg_initializing : std_logic;

  function f_bool_2_sl (x : boolean) return std_logic is
  begin
    if(x) then
      return '1';
    else
      return '0';
    end if;
  end f_bool_2_sl;

  function f_slv_resize(x : std_logic_vector; len : natural) return std_logic_vector is
    variable tmp : std_logic_vector(len-1 downto 0);
  begin
    tmp                      := (others => '0');
    tmp(x'length-1 downto 0) := x;
    return tmp;
  end f_slv_resize;

  
begin  -- syn

  
  gen_arbiter : for i in 0 to g_num_ports-1 generate

    ports(i).req_force_free <= force_free_i(i);
    ports(i).req_free       <= free_i(i);
    ports(i).req_alloc      <= alloc_i(i) and not (pg_nomem);
    ports(i).req_set_usecnt <= set_usecnt_i(i);


    process(ports, arb_req, arb_grant, pg_done)
    begin
      ports(i).grant_ib_d(0) <= arb_grant(2 * i);
      ports(i).grant_ob_d(0) <= arb_grant(2 * i + 1);

      ports(i).req_ib <= (ports(i).req_alloc or ports(i).req_set_usecnt);  -- and f_bool_2_sl(ports(i).grant_ib_d = "000");
      ports(i).req_ob <= (ports(i).req_free or ports(i).req_force_free);  -- and f_bool_2_sl(ports(i).grant_ob_d = "000");

      arb_req(2 * i)     <= ports(i).req_ib and not (pg_done and ports(i).grant_ib_d(0));
      arb_req(2 * i + 1) <= ports(i).req_ob and not (pg_done and ports(i).grant_ob_d(0));

    end process;

    --p_delay_grant : process(clk_i)
    --begin
    --  if rising_edge(clk_i) then
    --    if rst_n_i = '0' then
    --      ports(i).grant_ib_d(2 downto 1) <= "00";
    --      ports(i).grant_ob_d(2 downto 1) <= "00";
    --    else
    --      ports(i).grant_ib_d(1) <= ports(i).grant_ib_d(0);
    --      ports(i).grant_ib_d(2) <= ports(i).grant_ib_d(1);
    --      ports(i).grant_ob_d(1) <= ports(i).grant_ob_d(0);
    --      ports(i).grant_ob_d(2) <= ports(i).grant_ob_d(1);
    --    end if;
    --  end if;
    --end process;
  end generate gen_arbiter;

  p_arbitrate : process(clk_i)
  begin
    if rising_edge(clk_i) then
      if rst_n_i = '0'then
        arb_grant <= (others => '0');
      else
        f_rr_arbitrate(arb_req, arb_grant, arb_grant);
      end if;
    end if;
  end process;

  p_gen_pg_reqs : process(ports)
    variable alloc, free, force_free, set_usecnt : std_logic;
  begin
    alloc      := '0';
    free       := '0';
    force_free := '0';
    set_usecnt := '0';

    for i in 0 to g_num_ports-1 loop
      if(ports(i).grant_ib_d(0) = '1') then
        alloc      := ports(i).req_alloc;
        set_usecnt := ports(i).req_set_usecnt;
      end if;

      if(ports(i).grant_ob_d(0) = '1') then
        free       := ports(i).req_free;
        force_free := ports(i).req_force_free;
      end if;
    end loop;  -- i

    pg_alloc      <= alloc;
    pg_free       <= free;
    pg_force_free <= force_free;
    pg_set_usecnt <= set_usecnt;
  end process;


  p_mux_addr_usecnt_inputs : process(ports, pgaddr_usecnt_i, pgaddr_free_i, pgaddr_force_free_i, usecnt_i)
    variable tmp_addr : std_logic_vector(g_page_addr_width-1 downto 0);
    variable tmp_ucnt : std_logic_vector(g_usecount_width-1 downto 0);
  begin
    tmp_addr := (others => 'X');
    tmp_ucnt := (others => 'X');
    for i in 0 to g_num_ports-1 loop
      if(ports(i).grant_ib_d(0) = '1') then
        tmp_addr := pgaddr_usecnt_i(g_page_addr_width * (i+1) -1 downto g_page_addr_width*i);
        tmp_ucnt := usecnt_i(g_usecount_width * (i+1) - 1 downto g_usecount_width*i);
      elsif(ports(i).grant_ob_d(0) = '1') then
        if(ports(i).req_free = '1') then
          tmp_addr := pgaddr_free_i(g_page_addr_width * (i+1) -1 downto g_page_addr_width*i);
          tmp_ucnt := (others => 'X');
        elsif(ports(i).req_force_free = '1') then
          tmp_addr := pgaddr_force_free_i(g_page_addr_width * (i+1) -1 downto g_page_addr_width*i);
          tmp_ucnt := (others => 'X');
        end if;
      end if;
    end loop;  -- i
    pg_addr   <= tmp_addr;
    pg_usecnt <= tmp_ucnt;
  end process;

  -- one allocator/deallocator for all ports
  --ALLOC_CORE : swc_page_allocator_new -- tom's new allocator, not debugged, looses pages :(
  ALLOC_CORE : swc_page_allocator_new
    generic map (
      g_num_pages       => g_page_num,
      g_page_addr_width => g_page_addr_width,
      g_num_ports       => g_num_ports,
      g_usecount_width  => g_usecount_width)
    port map (
      clk_i                   => clk_i,
      rst_n_i                 => rst_n_i,
      alloc_i                 => pg_alloc,
      free_i                  => pg_free,
      free_last_usecnt_o      => pg_free_last_usecnt,
      force_free_i            => pg_force_free,
      set_usecnt_i            => pg_set_usecnt,
      usecnt_i                => pg_usecnt,
      pgaddr_i                => pg_addr,
      pgaddr_o                => pg_addr_alloc,
      done_o                  => pg_done,
      nomem_o                 => pg_nomem,
      dbg_double_force_free_o => dbg_double_force_free,
      dbg_double_free_o       => dbg_double_free,
      dbg_q_read_o            => dbg_q_read,
      dbg_q_write_o           => dbg_q_write,
      dbg_initializing_o      => dbg_initializing);

  nomem_o        <= pg_nomem;
  pgaddr_alloc_o <= pg_addr_alloc;

  p_gen_done : process(pg_done, ports)
  begin
    for i in 0 to g_num_ports-1 loop
      if(pg_done = '1') then
        alloc_done(i)      <= ports(i).req_alloc and ports(i).grant_ib_d(0);
        free_done(i)       <= ports(i).req_free and ports(i).grant_ob_d(0);
        force_free_done(i) <= ports(i).req_force_free and ports(i).grant_ob_d(0);
        set_usecnt_done(i) <= ports(i).req_set_usecnt and ports(i).grant_ib_d(0);
      else
        alloc_done(i)      <= '0';
        free_done(i)       <= '0';
        force_free_done(i) <= '0';
        set_usecnt_done(i) <= '0';
      end if;
    end loop;  -- i
  end process;

  alloc_done_o      <= alloc_done;
  free_done_o       <= free_done;
  force_free_done_o <= force_free_done;
  set_usecnt_done_o <= set_usecnt_done;

  free_last_usecnt_o <= (others => pg_free_last_usecnt);

  p_assertions : process(clk_i)
  begin
    if rising_edge(clk_i) then
      for i in 0 to g_num_ports-1 loop
        if(ports(i).req_alloc = '1' and ports(i).req_set_usecnt = '1') then
          report "simultaneous alloc/set_usecnt" severity failure;
          
        elsif (ports(i).req_free = '1' and ports(i).req_force_free = '1') then
          report "simultaneous free/force_free" severity failure;

        end if;

      end loop;  -- i
    end if;
  end process;

  tap_out_o <= f_slv_resize
               (
                 dbg_q_write &
                 dbg_q_read &
                 dbg_initializing &
                 alloc_i &
                 free_i &
                 force_free_i &
                 set_usecnt_i &

                 alloc_done&
                 free_done &
                 force_free_done&         -- 56
                 set_usecnt_done &        -- 48
                 pg_alloc &               -- 47
                 pg_free &                -- 46
                 pg_free_last_usecnt &    -- 45
                 pg_force_free &          -- 44
                 pg_set_usecnt &          -- 43
                 pg_usecnt &              -- 40
                 pg_addr &                -- 30
                 pg_addr_alloc &          -- 20
                 pg_done &                -- 19
                 pg_nomem &               -- 18
                 dbg_double_free &        -- 17
                 dbg_double_force_free ,  --  16
                 50 + 62);

end syn;
