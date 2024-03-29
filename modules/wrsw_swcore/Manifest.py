#files = ["swc_async_grow_fifo.vhd", 
#         "swc_async_fifo_ctrl.vhd", 
#         "swc_fifo_mem_cell.vhd",
#         "swc_async_shrink_fifo.vhd", 
#         "swc_private_pkg.vhd", 
#         "swc_pipelined_mux.vhd",
#         "swc_async_multiport_mem.vhd"]


files = [
"swc_core.vhd",
"swc_multiport_linked_list.vhd",

#"new_allocator/swc_multiport_page_allocator.vhd",
#"new_allocator/swc_page_alloc_ram_bug.vhd",


"old_allocator/swc_multiport_page_allocator.vhd",
"old_allocator/swc_page_alloc_old.vhd",

#"swc_multiport_page_allocator.vhd",
#"swc_page_alloc_old.vhd",


"swc_multiport_pck_pg_free_module.vhd",
"swc_ob_prio_queue.vhd",
#"swc_packet_mem.vhd",
#"swc_packet_mem_read_pump.vhd",
#"swc_packet_mem_write_pump.vhd",
#"swc_page_alloc.vhd",
"swc_pck_pg_free_module.vhd",
"swc_pck_transfer_arbiter.vhd",
"swc_pck_transfer_input.vhd",
"swc_pck_transfer_output.vhd",
"swc_prio_encoder.vhd",
"swc_rr_arbiter.vhd",
"xswc_core.vhd",
"xswc_output_block.vhd",
"xswc_input_block.vhd",
"../wrsw_shared_types_pkg.vhd",
"swc_ll_read_data_validation.vhd",
"swc_swcore_pkg.vhd",
"ram_bug/swc_rd_wr_ram.vhd"];

#"buggy_ram.vhd",
#"buggy_ram.ngc"]
modules = {"local": ["mpm"]}


if (action == "simulation"):
	files.append("ram_bug/buggy_ram_synth.vhd")
else:
	files.append("ram_bug/buggy_ram.ngc")
