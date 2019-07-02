/*
 * This file is licensed under the apache license
 * And is derived from https://github.com/imneme/pcg-c
 *
 */
#include "fancy.h"

static struct {
	u128 state, inc;
} state;

static const u128 MULTIPLIER = (((u128)2549297995355413924ull) << 64) + ((u128)4865540595714422341ull);

static inline u64 rotr(u64 value, u32 rot) {
	return (value >> rot) | (value << ((- rot) & 63));
}

static inline void step(void) {
	state.state = state.state * MULTIPLIER + state.inc;
}

static inline u64 output_rn(u128 st) {
	return rotr(((u64)(st >> 64u)) ^ (u64)st, st >> 122u);
}

void seed_random(u128 initstate, u128 initseq) {
	state.state = 0U;
	state.inc = (initseq << 1u) | 1u;
	step();
	state.state += initstate;
	step();
}
u64 random(void) {
	step();
	return output_rn(state.state);
}
u64 rnb(u64 bound) {
	u64 threshold = -bound % bound;
	loop {
		u64 r = random();
		if (r >= threshold)
			return r % bound;
	}
}
