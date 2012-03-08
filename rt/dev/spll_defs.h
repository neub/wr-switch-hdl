/*

White Rabbit Softcore PLL (SoftPLL) - common definitions

*/


#include <stdio.h>

/* Reference clock frequency */
#define CLOCK_FREQ 62500000

/* Bit size of phase tags generated by the DMTDs. Used to sign-extend the tags. */
#define TAG_BITS 22

/* Helper PLL N divider (1/2**N is the frequency offset) */
#define HPLL_N 14

/* Fractional bits in PI controller coefficients */
#define PI_FRACBITS 12

/* Max. number of reference channels */
#define MAX_CHAN_REF 7

/* Max. number of output channels */
#define MAX_CHAN_OUT 1
