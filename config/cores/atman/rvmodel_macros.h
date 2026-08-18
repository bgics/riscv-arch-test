#ifndef _RVMODEL_MACROS_H
#define _RVMODEL_MACROS_H

#define RVMODEL_DATA_SECTION

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

/* atman has no machine external/software interrupt mechanism to drive from
 * software; these exist only to satisfy check_defines.h. */
#define RVMODEL_SET_MEXT_INT(_R1, _R2)
#define RVMODEL_CLR_MEXT_INT(_R1, _R2)
#define RVMODEL_SET_MSW_INT(_R1, _R2)
#define RVMODEL_CLR_MSW_INT(_R1, _R2)

/* atman has no S-mode; these exist only to satisfy check_defines.h. */
#define RVMODEL_SET_SEXT_INT(_R1, _R2)
#define RVMODEL_CLR_SEXT_INT(_R1, _R2)
#define RVMODEL_SET_SSW_INT(_R1, _R2)
#define RVMODEL_CLR_SSW_INT(_R1, _R2)

#endif  // _RVMODEL_MACROS_H
