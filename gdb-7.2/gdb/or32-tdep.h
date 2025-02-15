/* Definitions to target GDB to OpenRISC 1000 32-bit targets.

   Copyright 2001 Free Software Foundation, Inc.
   Copyright (C) 2008, 2010 Embecosm Limited

   Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 3 of the License, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
   more details.

   You should have received a copy of the GNU General Public License along
   with this program.  If not, see <http://www.gnu.org/licenses/>.  */


#ifndef OR32_TDEP__H
#define OR32_TDEP__H

#ifndef TARGET_OR32
#define TARGET_OR32
#endif

/*-----------------------------------------------------------------------------
   This version for the OpenRISC 1000 architecture is a rewrite by Jeremy
   Bennett of the old GDB 5.3 interface to make use of gdbarch for GDB 6.8.

   The code tries to follow the GDB coding style. All OR32 specific globals
   should have names beginning ork1_ or OR32_.

   Commenting is Doxygen compatible.

   Much has been stripped out. See the files or32-tdep.c, remote-or32.c and
   or32-jtag.c for details of what has changed.
   --------------------------------------------------------------------------*/


/*! Byte array for the TRAP instruction used for breakpoints */
#define OR32_BRK_INSTR_STRUCT  {0x21, 0x00, 0x00, 0x01}
/*! Numeric instruction used for a breakpoint */
#define OR32_BRK_INSTR 0x21000001

/*! Numeric instruction used for a l.nop NOP_EXIT */
#define  OR32_NOP_EXIT 0x15000001

/* Special purpose groups */

#define OR32_SPG_SIZE_BITS  11
#define OR32_SPG_SIZE       (1 << OR32_SPG_SIZE_BITS)

#define OR32_SPG_SYS      0
#define OR32_SPG_DMMU     1
#define OR32_SPG_IMMU     2
#define OR32_SPG_DC       3
#define OR32_SPG_IC       4
#define OR32_SPG_MAC      5
#define OR32_SPG_DEBUG    6
#define OR32_SPG_PC       7
#define OR32_SPG_PM       8
#define OR32_SPG_PIC      9
#define OR32_SPG_TT      10
#define OR32_SPG_FPU     11

#define OR32_NUM_SPGS   (OR32_SPG_FPU + 1)

/* Special register group offsets */

#define OR32_SPG_SYS_VR          0
#define OR32_SPG_SYS_UPR         1
#define OR32_SPG_SYS_CPUCFGR     2
#define OR32_SPG_SYS_DMMUCFGR    3
#define OR32_SPG_SYS_IMMUCFGR    4
#define OR32_SPG_SYS_DCCFGR      5
#define OR32_SPG_SYS_ICCFGR      6
#define OR32_SPG_SYS_DCFGR       7
#define OR32_SPG_SYS_PCCFGR      8
#define OR32_SPG_SYS_NPC        16
#define OR32_SPG_SYS_SR         17
#define OR32_SPG_SYS_PPC        18
#define OR32_SPG_SYS_FPCSR      20
#define OR32_SPG_SYS_EPCR       32
#define OR32_SPG_SYS_EPCR_END  (OR32_SPG_SYS_EPCR + 15)
#define OR32_SPG_SYS_EEAR       48
#define OR32_SPG_SYS_EEAR_END  (OR32_SPG_SYS_EEAR + 15)
#define OR32_SPG_SYS_ESR        64
#define OR32_SPG_SYS_ESR_END   (OR32_SPG_SYS_ESR + 15)
#define OR32_SPG_SYS_GPR      1024
#define OR32_SPG_SYS_GPR_END   (OR32_SPG_SYS_GPR + OR32_MAX_GPR_REGS)
#define OR32_SPG_SYS_LAST       OR32_SPG_SYS_GPR_END

#define OR32_SPG_DMMU_DMMUCR           0
#define OR32_SPG_DMMU_DMMUPR           1
#define OR32_SPG_DMMU_DTLBEIR          2
#define OR32_SPG_DMMU_DATBMR           4
#define OR32_SPG_DMMU_DATBMR_END   (OR32_SPG_DMMU_DATBMR + 3)
#define OR32_SPG_DMMU_DATBTR           8
#define OR32_SPG_DMMU_DATBTR_END   (OR32_SPG_DMMU_DATBTR + 3)
#define OR32_SPG_DMMU_DTLBW0MR       512
#define OR32_SPG_DMMU_DTLBW0MR_END (OR32_SPG_DMMU_DTLBW0MR + 127)
#define OR32_SPG_DMMU_DTLBW0TR       640
#define OR32_SPG_DMMU_DTLBW0TR_END (OR32_SPG_DMMU_DTLBW0TR + 127)
#define OR32_SPG_DMMU_DTLBW1MR       768
#define OR32_SPG_DMMU_DTLBW1MR_END (OR32_SPG_DMMU_DTLBW1MR + 127)
#define OR32_SPG_DMMU_DTLBW1TR       896
#define OR32_SPG_DMMU_DTLBW1TR_END (OR32_SPG_DMMU_DTLBW1TR + 127)
#define OR32_SPG_DMMU_DTLBW2MR      1024
#define OR32_SPG_DMMU_DTLBW2MR_END (OR32_SPG_DMMU_DTLBW2MR + 127)
#define OR32_SPG_DMMU_DTLBW2TR      1152
#define OR32_SPG_DMMU_DTLBW2TR_END (OR32_SPG_DMMU_DTLBW2TR + 127)
#define OR32_SPG_DMMU_DTLBW3MR      1280
#define OR32_SPG_DMMU_DTLBW3MR_END (OR32_SPG_DMMU_DTLBW3MR + 127)
#define OR32_SPG_DMMU_DTLBW3TR      1408
#define OR32_SPG_DMMU_DTLBW3TR_END (OR32_SPG_DMMU_DTLBW3TR + 127)
#define OR32_SPG_DMMU_LAST          OR32_SPG_DMMU_DTLBW3TR_END

#define OR32_SPG_IMMU_IMMUCR           0
#define OR32_SPG_IMMU_IMMUPR           1
#define OR32_SPG_IMMU_ITLBEIR          2
#define OR32_SPG_IMMU_IATBMR           4
#define OR32_SPG_IMMU_IATBMR_END   (OR32_SPG_IMMU_IATBMR + 3)
#define OR32_SPG_IMMU_IATBTR           8
#define OR32_SPG_IMMU_IATBTR_END   (OR32_SPG_IMMU_IATBTR + 3)
#define OR32_SPG_IMMU_ITLBW0MR       512
#define OR32_SPG_IMMU_ITLBW0MR_END (OR32_SPG_IMMU_ITLBW0MR + 127)
#define OR32_SPG_IMMU_ITLBW0TR       640
#define OR32_SPG_IMMU_ITLBW0TR_END (OR32_SPG_IMMU_ITLBW0TR + 127)
#define OR32_SPG_IMMU_ITLBW1MR       768
#define OR32_SPG_IMMU_ITLBW1MR_END (OR32_SPG_IMMU_ITLBW1MR + 127)
#define OR32_SPG_IMMU_ITLBW1TR       896
#define OR32_SPG_IMMU_ITLBW1TR_END (OR32_SPG_IMMU_ITLBW1TR + 127)
#define OR32_SPG_IMMU_ITLBW2MR      1024
#define OR32_SPG_IMMU_ITLBW2MR_END (OR32_SPG_IMMU_ITLBW2MR + 127)
#define OR32_SPG_IMMU_ITLBW2TR      1152
#define OR32_SPG_IMMU_ITLBW2TR_END (OR32_SPG_IMMU_ITLBW2TR + 127)
#define OR32_SPG_IMMU_ITLBW3MR      1280
#define OR32_SPG_IMMU_ITLBW3MR_END (OR32_SPG_IMMU_ITLBW3MR + 127)
#define OR32_SPG_IMMU_ITLBW3TR      1408
#define OR32_SPG_IMMU_ITLBW3TR_END (OR32_SPG_IMMU_ITLBW3TR + 127)
#define OR32_SPG_IMMU_LAST          OR32_SPG_IMMU_ITLBW3TR_END

#define OR32_SPG_DC_DCCR   0
#define OR32_SPG_DC_DCBPR  1
#define OR32_SPG_DC_DCBFR  2
#define OR32_SPG_DC_DCBIR  3
#define OR32_SPG_DC_DCBWR  4
#define OR32_SPG_DC_DCBLR  5
#define OR32_SPG_DC_LAST   OR32_SPG_DC_DCBLR

#define OR32_SPG_IC_ICCR   0
#define OR32_SPG_IC_ICBPR  1
#define OR32_SPG_IC_ICBIR  2
#define OR32_SPG_IC_ICBLR  3
#define OR32_SPG_IC_LAST   OR32_SPG_IC_ICBLR

#define OR32_SPG_MAC_MACLO  1
#define OR32_SPG_MAC_MACHI  2
#define OR32_SPG_MAC_LAST   OR32_SPG_MAC_MACHI

#define OR32_SPG_DEBUG_DVR      0
#define OR32_SPG_DEBUG_DVR_END (OR32_SPG_DEBUG_DVR + 7)
#define OR32_SPG_DEBUG_DCR      8
#define OR32_SPG_DEBUG_DCR_END (OR32_SPG_DEBUG_DCR + 7)
#define OR32_SPG_DEBUG_DMR1   16
#define OR32_SPG_DEBUG_DMR2   17
#define OR32_SPG_DEBUG_DCWR0  18
#define OR32_SPG_DEBUG_DCWR1  19
#define OR32_SPG_DEBUG_DSR    20
#define OR32_SPG_DEBUG_DRR    21
#define OR32_SPG_DEBUG_LAST   OR32_SPG_DEBUG_DRR

#define OR32_SPG_PC_PCCR       0
#define OR32_SPG_PC_PCCR_END  (OR32_SPG_PC_PCCR + 7)
#define OR32_SPG_PC_PCMR       8
#define OR32_SPG_PC_PCMR_END  (OR32_SPG_PC_PCMR + 7)
#define OR32_SPG_PC_LAST       OR32_SPG_PC_PCMR_END

#define OR32_SPG_PM_PMR     0
#define OR32_SPG_PM_LAST    OR32_SPG_PM_PMR

#define OR32_SPG_PIC_PICMR  0
#define OR32_SPG_PIC_PICSR  2
#define OR32_SPG_PIC_LAST   OR32_SPG_PIC_PICSR

#define OR32_SPG_TT_TTMR    0
#define OR32_SPG_TT_TTCR    1
#define OR32_SPG_TT_LAST    OR32_SPG_TT_TTCR

#define OR32_SPG_FPU_LAST  -1


/* Define absolute SPR values from group and index  */
#define OR32_SPR(group, index) (((group) << OR32_SPG_SIZE_BITS) + (index))

/* System group registers */
#define OR32_VR_SPRNUM       OR32_SPR (OR32_SPG_SYS, OR32_SPG_SYS_VR)
#define OR32_UPR_SPRNUM      OR32_SPR (OR32_SPG_SYS, OR32_SPG_SYS_UPR)
#define OR32_CPUCFGR_SPRNUM  OR32_SPR (OR32_SPG_SYS, OR32_SPG_SYS_CPUCFGR)
#define OR32_DCFGR_SPRNUM    OR32_SPR (OR32_SPG_SYS, OR32_SPG_SYS_DCFGR)
#define OR32_NPC_SPRNUM      OR32_SPR (OR32_SPG_SYS, OR32_SPG_SYS_NPC)
#define OR32_SR_SPRNUM       OR32_SPR (OR32_SPG_SYS, OR32_SPG_SYS_SR)
#define OR32_PPC_SPRNUM      OR32_SPR (OR32_SPG_SYS, OR32_SPG_SYS_PPC)
#define OR32_EPCR_SPRNUM     OR32_SPR (OR32_SPG_SYS, OR32_SPG_SYS_EPCR)

/* Debug group registers */
#define OR32_DVR0_SPRNUM     OR32_SPR (OR32_SPG_DEBUG, OR32_SPG_DEBUG_DVR)
#define OR32_DCR0_SPRNUM     OR32_SPR (OR32_SPG_DEBUG, OR32_SPG_DEBUG_DCR)
#define OR32_DMR1_SPRNUM     OR32_SPR (OR32_SPG_DEBUG, OR32_SPG_DEBUG_DMR1)
#define OR32_DMR2_SPRNUM     OR32_SPR (OR32_SPG_DEBUG, OR32_SPG_DEBUG_DMR2)
#define OR32_DCWR0_SPRNUM    OR32_SPR (OR32_SPG_DEBUG, OR32_SPG_DEBUG_DCWR0)
#define OR32_DCWR1_SPRNUM    OR32_SPR (OR32_SPG_DEBUG, OR32_SPG_DEBUG_DCWR0)
#define OR32_DSR_SPRNUM      OR32_SPR (OR32_SPG_DEBUG, OR32_SPG_DEBUG_DSR)
#define OR32_DRR_SPRNUM      OR32_SPR (OR32_SPG_DEBUG, OR32_SPG_DEBUG_DRR)

/* General Purpose Registers */
#define OR32_ZERO_REGNUM          0
#define OR32_SP_REGNUM            1
#define OR32_FP_REGNUM            2
#define OR32_FIRST_ARG_REGNUM     3
#define OR32_LAST_ARG_REGNUM      8
#define OR32_LR_REGNUM            9
#define OR32_FIRST_SAVED_REGNUM  10
#define OR32_RV_REGNUM           11
#define OR32_PPC_REGNUM          (OR32_MAX_GPR_REGS + 0)
#define OR32_NPC_REGNUM          (OR32_MAX_GPR_REGS + 1)
#define OR32_SR_REGNUM           (OR32_MAX_GPR_REGS + 2)

/* Defines for Debug Control Register bits */

#define OR32_DCR_DP        0x0000001    /* DVR/DCR Present */
#define OR32_DCR_CC        0x000000e    /* Compare condition */
#define OR32_DCR_CC_OFF            1    /* Compare condition offset */
#define OR32_DCR_SC        0x0000010    /* Signed compare */
#define OR32_DCR_CT        0x00000e0    /* Compare type */
#define OR32_DCR_CT_OFF            5    /* Compare type offset */

/* Defines for Debug Mode Register 1 bits.  */
#define OR32_DMR1_CW       0x00000003   /* Mask for CW bits */
#define OR32_DMR1_CW_AND   0x00000001	/* Chain watchpoint 0 AND */
#define OR32_DMR1_CW_OR    0x00000002	/* Chain watchpoint 0 OR */
#define OR32_DMR1_CW_SZ             2   /* Number of bits for each WP */
#define OR32_DMR1_ST       0x00400000	/* Single-step trace */
#define OR32_DMR1_BT       0x00800000	/* Branch trace */

/* Defines for Debug Mode Register 2 bits.  */
#define OR32_DMR2_WCE0       0x00000001	/* Watchpoint counter enable 0 */
#define OR32_DMR2_WCE1       0x00000002	/* Watchpoint counter enable 1 */
#define OR32_DMR2_AWTC_MASK  0x00000ffc	/* Assign watchpoints to ctr mask */
#define OR32_DMR2_WGB_MASK   0x003ff000	/* Watchpoints generaing brk mask */
#define OR32_DMR2_WBS_MASK   0xffc00000 /* Watchpoint brkpt status mask */
#define OR32_DMR2_AWTC_OFF    2		/* Assign watchpoints to ctr offset */
#define OR32_DMR2_WGB_OFF    12		/* Watchpoints generating brk offset */
#define OR32_DMR2_WBS_OFF    22		/* Watchpoint brkpt status offset */

/* Defines for Debug Stop Register.  */
#define OR32_DSR_RSTE    0x00000001	/* Reset exception */
#define OR32_DSR_BUSEE   0x00000002	/* Bus error exception */
#define OR32_DSR_DPFE    0x00000004	/* Data page fault exception */
#define OR32_DSR_IPFE    0x00000008	/* Instrution page fault exception */
#define OR32_DSR_TTE     0x00000010	/* Tick timer exception */
#define OR32_DSR_AE      0x00000020	/* Alignment exception */
#define OR32_DSR_IIE     0x00000040	/* Illegal instruction exception */
#define OR32_DSR_INTE    0x00000080	/* Interrupt exception */
#define OR32_DSR_DME     0x00000100	/* DTLB miss exception */
#define OR32_DSR_IME     0x00000200	/* ITLB miss exception */
#define OR32_DSR_RE      0x00000400	/* Range exception */
#define OR32_DSR_SCE     0x00000800	/* System call exception */
#define OR32_DSR_FPE     0x00001000	/* Floating point exception */
#define OR32_DSR_TE      0x00002000	/* Trap exception */

/* Defines for Debug Reason Register bits */
#define OR32_DRR_RSTE    0x00000001	/* Reset exception */
#define OR32_DRR_BUSEE   0x00000002	/* Bus error exception */
#define OR32_DRR_DPFE    0x00000004	/* Data page fault exception */
#define OR32_DRR_IPFE    0x00000008	/* Instrution page fault exception */
#define OR32_DRR_TTE     0x00000010	/* Tick timer exception */
#define OR32_DRR_AE      0x00000020	/* Alignment exception */
#define OR32_DRR_IIE     0x00000040	/* Illegal instruction exception */
#define OR32_DRR_INTE    0x00000080	/* Interrupt exception */
#define OR32_DRR_DME     0x00000100	/* DTLB miss exception */
#define OR32_DRR_IME     0x00000200	/* ITLB miss exception */
#define OR32_DRR_RE      0x00000400	/* Range exception */
#define OR32_DRR_SCE     0x00000800	/* System call exception */
#define OR32_DRR_FPE     0x00001000	/* Floating point exception */
#define OR32_DRR_TE      0x00002000	/* Trap exception */

/* Bit definitions for the Unit Present Register */
#define OR32_SPR_UPR_UP	        0x00000001  /* UPR present */
#define OR32_SPR_UPR_DCP        0x00000002  /* Data cache present */
#define OR32_SPR_UPR_ICP        0x00000004  /* Instruction cache present */
#define OR32_SPR_UPR_DMP        0x00000008  /* Data MMU present */
#define OR32_SPR_UPR_IMP        0x00000010  /* Instruction MMU present */
#define OR32_SPR_UPR_MP         0x00000020  /* MAC present */
#define OR32_SPR_UPR_DUP        0x00000040  /* Debug unit present */
#define OR32_SPR_UPR_PCUP       0x00000080  /* Perf counters unit present */
#define OR32_SPR_UPR_PMP        0x00000100  /* Power management present */
#define OR32_SPR_UPR_PICP       0x00000200  /* PIC present */
#define OR32_SPR_UPR_TTP        0x00000400  /* Tick timer present */

/* Bit definitions for the CPU Configuration Register */
#define OR32_SPR_CPUCFGR_NSGF   0x0000000f  /* Number of shadow GPR files */
#define OR32_SPR_CPUCFGR_CGF    0x00000010  /* Custom GPR file */
#define OR32_SPR_CPUCFGR_OB32S  0x00000020  /* ORBIS32 supported */
#define OR32_SPR_CPUCFGR_OB64S  0x00000040  /* ORBIS64 supported */
#define OR32_SPR_CPUCFGR_OF32S  0x00000080  /* ORFPX32 supported */
#define OR32_SPR_CPUCFGR_OF64S  0x00000100  /* ORFPX64 supported */
#define OR32_SPR_CPUCFGR_OV64S  0x00000400  /* ORVDX64 supported */

/* Bit definitions for the Debug configuration register */
#define OR32_SPR_DCFGR_NDP      0x00000007  /* Number of matchpoints */
#define OR32_SPR_DCFGR_WPCI     0x00000008  /* Watchpoint ctrs implemented */

/* Properties of the architecture. GDB mapping of registers is all the GPRs
   followed by the PPC, NPC and SR at the end. Red zone is the area past the
   end of the stack reserved for exception handlers etc. */
#define OR32_MAX_GPR_REGS           32
#define OR32_NUM_PSEUDO_REGS         0
#define OR32_NUM_REGS               (OR32_MAX_GPR_REGS + 3)
#define OR32_TOTAL_NUM_REGS         (OR32_NUM_REGS + OR32_NUM_PSEUDO_REGS)
#define OR32_MAX_MATCHPOINTS         8
#define OR32_MAX_HW_WATCHES          OR32_MAX_MATCHPOINTS
#define OR32_STACK_ALIGN             4
#define OR32_INSTLEN                 4
#define OR32_INSTBITLEN              (OR32_INSTLEN * 8)
#define OR32_NUM_TAP_RECORDS         8
#define OR32_FRAME_RED_ZONE_SIZE  2536

/* OR32 exception vectors */

#define OR32_RESET_VECTOR   0x100
#define OR32_BUSERR_VECTOR  0x200
#define OR32_DPF_VECTOR     0x300
#define OR32_IPF_VECTOR     0x400
#define OR32_TT_VECTOR      0x500
#define OR32_ALIGN_VECTOR   0x600
#define OR32_ILL_VECTOR     0x700
#define OR32_EXT_VECTOR     0x800
#define OR32_DTLB_VECTOR    0x900
#define OR32_ITLB_VECTOR    0xa00
#define OR32_RANGE_VECTOR   0xb00
#define OR32_SYS_VECTOR     0xc00
#define OR32_FP_VECTOR      0xd00
#define OR32_TRAP_VECTOR    0xe00

/* Constants and macros to break out instruction fields. I'd expect these in
   the assembler header, but they aren't there (for now). */

#define OR32_SEXT16(v) (((v) & 0x00008000) ? ((v) - 0x00010000) : (v))
#define OR32_SEXT26(v) (((v) & 0x02000000) ? ((v) - 0x04000000) : (v))

#define OR32_OPCODE1(i)  (((i) & 0xfc000000) >> 26)
#define OR32_OPCODE2(i) ((((i) & 0xfc000000) >> 20) | \
			 (((i) & 0x00000300) >>  6) | \
			  ((i) & 0x0000000f))
#define OR32_OPCODE3(i) ((((i) & 0xfc000000) >> 24) | \
			 (((i) & 0x000000c0) >> 6))
#define OR32_OPCODE4(i) ((((i) & 0xfc000000) >> 18) | \
			 (((i) & 0x000003c0) >>  2) | \
			  ((i) & 0x0000000f))
#define OR32_OPCODE5(i)  (((i) & 0xffff0000) >> 16)
#define OR32_OPCODE6(i)  (((i) & 0xff000000) >> 24)
#define OR32_OPCODE7(i)  (((i) & 0xfc000000) >> 21)
#define OR32_D_REG(i)    (((i) & 0x03e00000) >> 21)
#define OR32_A_REG(i)    (((i) & 0x001f0000) >> 16)
#define OR32_B_REG(i)    (((i) & 0x0000f800) >> 11)
#define OR32_IMM(i)      (OR32_SEXT16((i) & 0x0000ffff))
#define OR32_IMM2(i)     (OR32_SEXT16((((i) & 0x03e00000) >> 10) |	\
				       ((i) & 0x000003ff)))
#define OR32_OFFSET(i)    (OR32_SEXT26((i) & 0x03ffffff) ))
#define OR32_SHIFT(i)     ((i) & 0x0000003f)

/* The instruction opcodes */

#define OR32_OP_ADD     0xe00	/* Type 2 */
#define OR32_OP_ADDC    0xe01	/* Type 2 */
#define OR32_OP_ADDI     0x27	/* Type 1 */
#define OR32_OP_AND     0xe03	/* Type 2 */
#define OR32_OP_ANDI     0x29	/* Type 1 */
#define OR32_OP_BF       0x04	/* Type 1 */
#define OR32_OP_BNF      0x03	/* Type 1 */
#define OR32_OP_TRAP   0x2100	/* Type 5 */
#define OR32_OP_J        0x00	/* Type 1 */
#define OR32_OP_JAL      0x01	/* Type 1 */
#define OR32_OP_JALR     0x12	/* Type 1 */
#define OR32_OP_JR       0x11	/* Type 1 */
#define OR32_OP_LBS      0x24   /* Type 1 */
#define OR32_OP_LBZ      0x23   /* Type 1 */
#define OR32_OP_LHS      0x26   /* Type 1 */
#define OR32_OP_LHZ      0x25   /* Type 1 */
#define OR32_OP_LWS      0x22   /* Type 1 */
#define OR32_OP_LWZ      0x21   /* Type 1 */
#define OR32_OP_MFSPR    0x07   /* Type 1 */
#define OR32_OP_MOVHI    0x06   /* Type 1 */
#define OR32_OP_MTSPR    0x10   /* Type 1 */
#define OR32_OP_MUL     0xe36   /* Type 2 */
#define OR32_OP_MULI     0x2c   /* Type 1 */
#define OR32_OP_MULU    0xe3b   /* Type 2 */
#define OR32_OP_NOP      0x15   /* Type 6 */
#define OR32_OP_OR      0xe04	/* Type 2 */
#define OR32_OP_ORI      0x2a   /* Type 1 */
#define OR32_OP_RFE      0x09   /* Type 1 */
#define OR32_OP_RORI     0xe3   /* Type 3 */
#define OR32_OP_SB       0x36   /* Type 1 */
#define OR32_OP_SFEQ    0x720   /* Type 7 */
#define OR32_OP_SFGES   0x72b   /* Type 7 */
#define OR32_OP_SFGEU   0x723   /* Type 7 */
#define OR32_OP_SFGTS   0x72a   /* Type 7 */
#define OR32_OP_SFGTU   0x722   /* Type 7 */
#define OR32_OP_SFLES   0x72d   /* Type 7 */
#define OR32_OP_SFLEU   0x725   /* Type 7 */
#define OR32_OP_SFLTS   0x72c   /* Type 7 */
#define OR32_OP_SFLTU   0x724   /* Type 7 */
#define OR32_OP_SFNE    0x721   /* Type 7 */
#define OR32_OP_SLL    0x3808   /* Type 4 */
#define OR32_OP_SLLI     0xe0   /* Type 3 */
#define OR32_OP_SRA    0x3828   /* Type 4 */
#define OR32_OP_SRAI     0xe2   /* Type 3 */
#define OR32_OP_SRL    0x3818   /* Type 4 */
#define OR32_OP_SRLI     0xe1   /* Type 3 */
#define OR32_OP_SUB     0xe02   /* Type 2 */
#define OR32_OP_SW       0x35   /* Type 1 */
#define OR32_OP_SYS    0x2000   /* Type 5 */
#define OR32_OP_XOR     0xe05   /* Type 2 */
#define OR32_OP_XORI     0x2b   /* Type 1 */


/*! OR32 specific per-architecture information. Replaces
    struct_or32_implementation. A lot of this info comes from the config regs,
    so cannot be put in place until we have the actual target. Up until then
    we have reasonable defaults. */
struct gdbarch_tdep
{
  unsigned int  num_matchpoints;	/* Total matchpoints available. */
  unsigned int  num_gpr_regs;		/* Number of general registers.  */
  int           bytes_per_word;
  int           bytes_per_address;
};

/* Global variable controlling frame debug messages */
extern int  frame_debug;

/* Global disassembly instructions */
extern int  print_insn_big_or32 (bfd_vma                  memaddr,
				 struct disassemble_info *info);
extern int  print_insn_little_or32 (bfd_vma                  memaddr,
				    struct disassemble_info *info);

#endif /* OR32_TDEP__H */
