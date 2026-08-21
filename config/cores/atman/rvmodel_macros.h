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
#define RVMODEL_HALT_ADDRESS 0x0FFFFF0
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

#define RVMODEL_INTERRUPT_LATENCY 1
#define RVMODEL_TIMER_INT_SOON_DELAY 100
#define RVMODEL_MAX_CYCLES_PER_TIMER_TICK 1

/* ACT4 requires these names in every configuration. They are inert because
 * this configuration excludes InterruptsSm and provides no interrupt source. */
#define RVMODEL_SET_MEXT_INT(_R1, _R2)
#define RVMODEL_CLR_MEXT_INT(_R1, _R2)
#define RVMODEL_SET_MSW_INT(_R1, _R2)
#define RVMODEL_CLR_MSW_INT(_R1, _R2)

/* Required inert compatibility stubs; S-mode is not implemented. */
#define RVMODEL_SET_SEXT_INT(_R1, _R2)
#define RVMODEL_CLR_SEXT_INT(_R1, _R2)
#define RVMODEL_SET_SSW_INT(_R1, _R2)
#define RVMODEL_CLR_SSW_INT(_R1, _R2)

#endif  // _RVMODEL_MACROS_H
