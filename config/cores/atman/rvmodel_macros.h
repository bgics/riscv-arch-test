#ifndef _RVMODEL_MACROS_H
#define _RVMODEL_MACROS_H

#define RVMODEL_DATA_SECTION

/* Enable ACT4's standard M-mode exception environment. */
#define STANDARD_SM_SUPPORTED

/* Use the standard M-mode trap setup without touching unimplemented HPM CSRs.
 */
#define RVMODEL_BOOT_TO_MMODE \
  rvtest_boot_to_mmode:       \
  csrw mie, zero;             \
  csrw mip, zero;             \
  csrw mepc, zero;            \
  csrw mtval, zero;           \
  csrw mcause, zero;          \
  RVTEST_TRAP_PROLOG M;       \
  li t0, MSTATUS_MPP;         \
  csrw mstatus, t0;

/* Fixed location in RAM that the testbench monitors for pass/fail.
 * Must lie inside the DUT's data memory and not collide with test data,
 * the stack, or the signature region. Top of the 16 MiB unified RAM. */
#define RVMODEL_HALT_ADDRESS 0x04000000
#define RVMODEL_HALT_PASS_VALUE 1
#define RVMODEL_HALT_FAIL_VALUE 3

#define RVMODEL_HALT_PASS         \
  li t0, RVMODEL_HALT_ADDRESS;    \
  li t1, RVMODEL_HALT_PASS_VALUE; \
  sw t1, 0(t0);                   \
  1 : j 1b;

#define RVMODEL_HALT_FAIL         \
  li t0, RVMODEL_HALT_ADDRESS;    \
  li t1, RVMODEL_HALT_FAIL_VALUE; \
  sw t1, 0(t0);                   \
  1 : j 1b;

#define RVMODEL_IO_WRITE_STR(_R1, _R2, _R3, _STR_PTR)

/* CLINT timer registers. The DUT's CLINT decodes MTIMECMP at 0x02004000
 * (lo) / 0x02004004 (hi) and MTIME at 0x0200BFF8 (lo) / 0x0200BFFC (hi).
 * ACT4 generates the timer arm/clear sequences from these addresses; without
 * them the framework assumes no timer is implemented and emits no code. */
#define RVMODEL_MTIME_ADDRESS 0x0200BFF8
#define RVMODEL_MTIMECMP_ADDRESS 0x02004000

#define RVMODEL_INTERRUPT_LATENCY 2
#define RVMODEL_TIMER_INT_SOON_DELAY 50
#define RVMODEL_MAX_CYCLES_PER_TIMER_TICK 1

/* Functional macros for software interrupts (CLINT MSIP at 0x02000000).
 * Writing 1 to the MSIP address raises the software-interrupt pending
 * bit for hart 0; writing 0 clears it. */
#define RVMODEL_SET_MSW_INT(_R1, _R2) \
  li _R1, 0x02000000;                 \
  li _R2, 1;                          \
  sw _R2, 0(_R1)

#define RVMODEL_CLR_MSW_INT(_R1, _R2) \
  li _R1, 0x02000000;                 \
  sw zero, 0(_R1)

/* Functional macros for external interrupts (SIG at 0x03000000).
 * Write 0x80000800 to SIG+4 (0x03000004) sets MEIP (bit 11) on;
 * write 0x00000800 clears it. */
#define RVMODEL_SET_MEXT_INT(_R1, _R2) \
  li _R1, 0x03000004;                  \
  li _R2, 0x80000800;                  \
  sw _R2, 0(_R1)

#define RVMODEL_CLR_MEXT_INT(_R1, _R2) \
  li _R1, 0x03000004;                  \
  li _R2, 0x00000800;                  \
  sw _R2, 0(_R1)

/* Required inert compatibility stubs; S-mode is not implemented. */
#define RVMODEL_SET_SEXT_INT(_R1, _R2)
#define RVMODEL_CLR_SEXT_INT(_R1, _R2)
#define RVMODEL_SET_SSW_INT(_R1, _R2)
#define RVMODEL_CLR_SSW_INT(_R1, _R2)

#endif  // _RVMODEL_MACROS_H
