/*
  Register definitions for slave core: WR Softcore PLL

  * File           : softpll_regs.h
  * Author         : auto-generated by wbgen2 from spll_wb_slave.wb
  * Created        : Mon Apr 16 16:49:35 2012
  * Standard       : ANSI C

    THIS FILE WAS GENERATED BY wbgen2 FROM SOURCE FILE spll_wb_slave.wb
    DO NOT HAND-EDIT UNLESS IT'S ABSOLUTELY NECESSARY!

*/

#ifndef __WBGEN2_REGDEFS_SPLL_WB_SLAVE_WB
#define __WBGEN2_REGDEFS_SPLL_WB_SLAVE_WB

#if defined( __GNUC__)
#define PACKED __attribute__ ((packed))
#else
#error "Unsupported compiler?"
#endif

#ifndef __WBGEN2_MACROS_DEFINED__
#define __WBGEN2_MACROS_DEFINED__
#define WBGEN2_GEN_MASK(offset, size) (((1<<(size))-1) << (offset))
#define WBGEN2_GEN_WRITE(value, offset, size) (((value) & ((1<<(size))-1)) << (offset))
#define WBGEN2_GEN_READ(reg, offset, size) (((reg) >> (offset)) & ((1<<(size))-1))
#define WBGEN2_SIGN_EXTEND(value, bits) (((value) & (1<<bits) ? ~((1<<(bits))-1): 0 ) | (value))
#endif


/* definitions for register: SPLL Control/Status Register */

/* definitions for field: Period detector reference select in reg: SPLL Control/Status Register */
#define SPLL_CSR_PER_SEL_MASK                 WBGEN2_GEN_MASK(0, 6)
#define SPLL_CSR_PER_SEL_SHIFT                0
#define SPLL_CSR_PER_SEL_W(value)             WBGEN2_GEN_WRITE(value, 0, 6)
#define SPLL_CSR_PER_SEL_R(reg)               WBGEN2_GEN_READ(reg, 0, 6)

/* definitions for field: Number of reference channels (max: 32) in reg: SPLL Control/Status Register */
#define SPLL_CSR_N_REF_MASK                   WBGEN2_GEN_MASK(8, 6)
#define SPLL_CSR_N_REF_SHIFT                  8
#define SPLL_CSR_N_REF_W(value)               WBGEN2_GEN_WRITE(value, 8, 6)
#define SPLL_CSR_N_REF_R(reg)                 WBGEN2_GEN_READ(reg, 8, 6)

/* definitions for field: Number of output channels (max: 8) in reg: SPLL Control/Status Register */
#define SPLL_CSR_N_OUT_MASK                   WBGEN2_GEN_MASK(16, 3)
#define SPLL_CSR_N_OUT_SHIFT                  16
#define SPLL_CSR_N_OUT_W(value)               WBGEN2_GEN_WRITE(value, 16, 3)
#define SPLL_CSR_N_OUT_R(reg)                 WBGEN2_GEN_READ(reg, 16, 3)

/* definitions for field: Enable Period Measurement in reg: SPLL Control/Status Register */
#define SPLL_CSR_PER_EN                       WBGEN2_GEN_MASK(19, 1)

/* definitions for register: External Clock Control Register */

/* definitions for field: Enable External Clock BB Detector in reg: External Clock Control Register */
#define SPLL_ECCR_EXT_EN                      WBGEN2_GEN_MASK(0, 1)

/* definitions for field: External Clock Input Available in reg: External Clock Control Register */
#define SPLL_ECCR_EXT_SUPPORTED               WBGEN2_GEN_MASK(1, 1)

/* definitions for field: Enable PPS/phase alignment in reg: External Clock Control Register */
#define SPLL_ECCR_ALIGN_EN                    WBGEN2_GEN_MASK(2, 1)

/* definitions for field: PPS/phase alignment done in reg: External Clock Control Register */
#define SPLL_ECCR_ALIGN_DONE                  WBGEN2_GEN_MASK(3, 1)

/* definitions for field: External Clock Reference Present in reg: External Clock Control Register */
#define SPLL_ECCR_EXT_REF_PRESENT             WBGEN2_GEN_MASK(4, 1)

/* definitions for register: DMTD Clock Control Register */

/* definitions for field: DMTD Clock Undersampling Divider in reg: DMTD Clock Control Register */
#define SPLL_DCCR_GATE_DIV_MASK               WBGEN2_GEN_MASK(0, 6)
#define SPLL_DCCR_GATE_DIV_SHIFT              0
#define SPLL_DCCR_GATE_DIV_W(value)           WBGEN2_GEN_WRITE(value, 0, 6)
#define SPLL_DCCR_GATE_DIV_R(reg)             WBGEN2_GEN_READ(reg, 0, 6)

/* definitions for register: Reference Channel Undersampling Enable Register */

/* definitions for field: Reference Channel Undersampling Enable in reg: Reference Channel Undersampling Enable Register */
#define SPLL_RCGER_GATE_SEL_MASK              WBGEN2_GEN_MASK(0, 32)
#define SPLL_RCGER_GATE_SEL_SHIFT             0
#define SPLL_RCGER_GATE_SEL_W(value)          WBGEN2_GEN_WRITE(value, 0, 32)
#define SPLL_RCGER_GATE_SEL_R(reg)            WBGEN2_GEN_READ(reg, 0, 32)

/* definitions for register: Output Channel Control Register */

/* definitions for field: Output Channel HW enable flag in reg: Output Channel Control Register */
#define SPLL_OCCR_OUT_EN_MASK                 WBGEN2_GEN_MASK(0, 8)
#define SPLL_OCCR_OUT_EN_SHIFT                0
#define SPLL_OCCR_OUT_EN_W(value)             WBGEN2_GEN_WRITE(value, 0, 8)
#define SPLL_OCCR_OUT_EN_R(reg)               WBGEN2_GEN_READ(reg, 0, 8)

/* definitions for field: Output Channel locked flag in reg: Output Channel Control Register */
#define SPLL_OCCR_OUT_LOCK_MASK               WBGEN2_GEN_MASK(8, 8)
#define SPLL_OCCR_OUT_LOCK_SHIFT              8
#define SPLL_OCCR_OUT_LOCK_W(value)           WBGEN2_GEN_WRITE(value, 8, 8)
#define SPLL_OCCR_OUT_LOCK_R(reg)             WBGEN2_GEN_READ(reg, 8, 8)

/* definitions for register: Reference Channel Enable Register */

/* definitions for register: Output Channel Enable Register */

/* definitions for register: HPLL Period Error */

/* definitions for field: Period error value in reg: HPLL Period Error */
#define SPLL_PER_HPLL_ERROR_MASK              WBGEN2_GEN_MASK(0, 16)
#define SPLL_PER_HPLL_ERROR_SHIFT             0
#define SPLL_PER_HPLL_ERROR_W(value)          WBGEN2_GEN_WRITE(value, 0, 16)
#define SPLL_PER_HPLL_ERROR_R(reg)            WBGEN2_GEN_READ(reg, 0, 16)

/* definitions for field: Period Error Valid in reg: HPLL Period Error */
#define SPLL_PER_HPLL_VALID                   WBGEN2_GEN_MASK(16, 1)

/* definitions for register: Helper DAC Output */

/* definitions for register: Main DAC Output */

/* definitions for field: DAC value in reg: Main DAC Output */
#define SPLL_DAC_MAIN_VALUE_MASK              WBGEN2_GEN_MASK(0, 16)
#define SPLL_DAC_MAIN_VALUE_SHIFT             0
#define SPLL_DAC_MAIN_VALUE_W(value)          WBGEN2_GEN_WRITE(value, 0, 16)
#define SPLL_DAC_MAIN_VALUE_R(reg)            WBGEN2_GEN_READ(reg, 0, 16)

/* definitions for field: DAC select in reg: Main DAC Output */
#define SPLL_DAC_MAIN_DAC_SEL_MASK            WBGEN2_GEN_MASK(16, 4)
#define SPLL_DAC_MAIN_DAC_SEL_SHIFT           16
#define SPLL_DAC_MAIN_DAC_SEL_W(value)        WBGEN2_GEN_WRITE(value, 16, 4)
#define SPLL_DAC_MAIN_DAC_SEL_R(reg)          WBGEN2_GEN_READ(reg, 16, 4)

/* definitions for register: Deglitcher threshold */

/* definitions for register: Debug FIFO Register - SPLL side */

/* definitions for field: Debug Value in reg: Debug FIFO Register - SPLL side */
#define SPLL_DFR_SPLL_VALUE_MASK              WBGEN2_GEN_MASK(0, 31)
#define SPLL_DFR_SPLL_VALUE_SHIFT             0
#define SPLL_DFR_SPLL_VALUE_W(value)          WBGEN2_GEN_WRITE(value, 0, 31)
#define SPLL_DFR_SPLL_VALUE_R(reg)            WBGEN2_GEN_READ(reg, 0, 31)

/* definitions for field: End-of-Sample in reg: Debug FIFO Register - SPLL side */
#define SPLL_DFR_SPLL_EOS_MASK                WBGEN2_GEN_MASK(31, 1)
#define SPLL_DFR_SPLL_EOS_SHIFT               31
#define SPLL_DFR_SPLL_EOS_W(value)            WBGEN2_GEN_WRITE(value, 31, 1)
#define SPLL_DFR_SPLL_EOS_R(reg)              WBGEN2_GEN_READ(reg, 31, 1)

/* definitions for register: Interrupt disable register */

/* definitions for field: Got a tag in reg: Interrupt disable register */
#define SPLL_EIC_IDR_TAG                      WBGEN2_GEN_MASK(0, 1)

/* definitions for register: Interrupt enable register */

/* definitions for field: Got a tag in reg: Interrupt enable register */
#define SPLL_EIC_IER_TAG                      WBGEN2_GEN_MASK(0, 1)

/* definitions for register: Interrupt mask register */

/* definitions for field: Got a tag in reg: Interrupt mask register */
#define SPLL_EIC_IMR_TAG                      WBGEN2_GEN_MASK(0, 1)

/* definitions for register: Interrupt status register */

/* definitions for field: Got a tag in reg: Interrupt status register */
#define SPLL_EIC_ISR_TAG                      WBGEN2_GEN_MASK(0, 1)

/* definitions for register: FIFO 'Debug FIFO Register - Host side' data output register 0 */

/* definitions for field: Value in reg: FIFO 'Debug FIFO Register - Host side' data output register 0 */
#define SPLL_DFR_HOST_R0_VALUE_MASK           WBGEN2_GEN_MASK(0, 32)
#define SPLL_DFR_HOST_R0_VALUE_SHIFT          0
#define SPLL_DFR_HOST_R0_VALUE_W(value)       WBGEN2_GEN_WRITE(value, 0, 32)
#define SPLL_DFR_HOST_R0_VALUE_R(reg)         WBGEN2_GEN_READ(reg, 0, 32)

/* definitions for register: FIFO 'Debug FIFO Register - Host side' data output register 1 */

/* definitions for field: Seq ID in reg: FIFO 'Debug FIFO Register - Host side' data output register 1 */
#define SPLL_DFR_HOST_R1_SEQ_ID_MASK          WBGEN2_GEN_MASK(0, 16)
#define SPLL_DFR_HOST_R1_SEQ_ID_SHIFT         0
#define SPLL_DFR_HOST_R1_SEQ_ID_W(value)      WBGEN2_GEN_WRITE(value, 0, 16)
#define SPLL_DFR_HOST_R1_SEQ_ID_R(reg)        WBGEN2_GEN_READ(reg, 0, 16)

/* definitions for register: FIFO 'Debug FIFO Register - Host side' control/status register */

/* definitions for field: FIFO full flag in reg: FIFO 'Debug FIFO Register - Host side' control/status register */
#define SPLL_DFR_HOST_CSR_FULL                WBGEN2_GEN_MASK(16, 1)

/* definitions for field: FIFO empty flag in reg: FIFO 'Debug FIFO Register - Host side' control/status register */
#define SPLL_DFR_HOST_CSR_EMPTY               WBGEN2_GEN_MASK(17, 1)

/* definitions for field: FIFO counter in reg: FIFO 'Debug FIFO Register - Host side' control/status register */
#define SPLL_DFR_HOST_CSR_USEDW_MASK          WBGEN2_GEN_MASK(0, 13)
#define SPLL_DFR_HOST_CSR_USEDW_SHIFT         0
#define SPLL_DFR_HOST_CSR_USEDW_W(value)      WBGEN2_GEN_WRITE(value, 0, 13)
#define SPLL_DFR_HOST_CSR_USEDW_R(reg)        WBGEN2_GEN_READ(reg, 0, 13)

/* definitions for register: FIFO 'Tag Readout Register' data output register 0 */

/* definitions for field: Tag value in reg: FIFO 'Tag Readout Register' data output register 0 */
#define SPLL_TRR_R0_VALUE_MASK                WBGEN2_GEN_MASK(0, 24)
#define SPLL_TRR_R0_VALUE_SHIFT               0
#define SPLL_TRR_R0_VALUE_W(value)            WBGEN2_GEN_WRITE(value, 0, 24)
#define SPLL_TRR_R0_VALUE_R(reg)              WBGEN2_GEN_READ(reg, 0, 24)

/* definitions for field: Channel ID in reg: FIFO 'Tag Readout Register' data output register 0 */
#define SPLL_TRR_R0_CHAN_ID_MASK              WBGEN2_GEN_MASK(24, 7)
#define SPLL_TRR_R0_CHAN_ID_SHIFT             24
#define SPLL_TRR_R0_CHAN_ID_W(value)          WBGEN2_GEN_WRITE(value, 24, 7)
#define SPLL_TRR_R0_CHAN_ID_R(reg)            WBGEN2_GEN_READ(reg, 24, 7)

/* definitions for field: Discontinuous bit in reg: FIFO 'Tag Readout Register' data output register 0 */
#define SPLL_TRR_R0_DISC                      WBGEN2_GEN_MASK(31, 1)

/* definitions for register: FIFO 'Tag Readout Register' control/status register */

/* definitions for field: FIFO empty flag in reg: FIFO 'Tag Readout Register' control/status register */
#define SPLL_TRR_CSR_EMPTY                    WBGEN2_GEN_MASK(17, 1)

PACKED struct SPLL_WB {
  /* [0x0]: REG SPLL Control/Status Register */
  uint32_t CSR;
  /* [0x4]: REG External Clock Control Register */
  uint32_t ECCR;
  /* [0x8]: REG DMTD Clock Control Register */
  uint32_t DCCR;
  /* [0xc]: REG Reference Channel Undersampling Enable Register */
  uint32_t RCGER;
  /* [0x10]: REG Output Channel Control Register */
  uint32_t OCCR;
  /* [0x14]: REG Reference Channel Enable Register */
  uint32_t RCER;
  /* [0x18]: REG Output Channel Enable Register */
  uint32_t OCER;
  /* [0x1c]: REG HPLL Period Error */
  uint32_t PER_HPLL;
  /* [0x20]: REG Helper DAC Output */
  uint32_t DAC_HPLL;
  /* [0x24]: REG Main DAC Output */
  uint32_t DAC_MAIN;
  /* [0x28]: REG Deglitcher threshold */
  uint32_t DEGLITCH_THR;
  /* [0x2c]: REG Debug FIFO Register - SPLL side */
  uint32_t DFR_SPLL;
  /* padding to: 16 words */
  uint32_t __padding_0[4];
  /* [0x40]: REG Interrupt disable register */
  uint32_t EIC_IDR;
  /* [0x44]: REG Interrupt enable register */
  uint32_t EIC_IER;
  /* [0x48]: REG Interrupt mask register */
  uint32_t EIC_IMR;
  /* [0x4c]: REG Interrupt status register */
  uint32_t EIC_ISR;
  /* [0x50]: REG FIFO 'Debug FIFO Register - Host side' data output register 0 */
  uint32_t DFR_HOST_R0;
  /* [0x54]: REG FIFO 'Debug FIFO Register - Host side' data output register 1 */
  uint32_t DFR_HOST_R1;
  /* [0x58]: REG FIFO 'Debug FIFO Register - Host side' control/status register */
  uint32_t DFR_HOST_CSR;
  /* [0x5c]: REG FIFO 'Tag Readout Register' data output register 0 */
  uint32_t TRR_R0;
  /* [0x60]: REG FIFO 'Tag Readout Register' control/status register */
  uint32_t TRR_CSR;
};

#endif
