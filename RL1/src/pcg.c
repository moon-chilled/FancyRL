/*
 * This file is licensed under the apache license
 * And is derived from https://github.com/imneme/pcg-c
 *
 */
#include "fancy.h"

static const u128 MULTIPLIER = (((u128)2549297995355413924ull) << 64) + ((u128)4865540595714422341ull);

static inline u64 rotr(u64 value, u32 rot) {
	return (value >> rot) | (value << ((- rot) & 63));
}

static inline void step(RngState *state) {
	state->state = state->state * MULTIPLIER + state->inc;
}

static inline u64 output_rn(u128 state) {
	return rotr(((u64)(state >> 64u)) ^ (u64)state, state >> 122u);
}

void seed_random(RngState *state, u128 initstate, u128 initseq) {
	state->state = 0U;
	state->inc = (initseq << 1u) | 1u;
	step(state);
	state->state += initstate;
	step(state);
}
u64 random(RngState *state) {
	step(state);
	return output_rn(state->state);
}
u64 rnb(RngState *state, u64 bound) {
	u64 threshold = -bound % bound;
	loop {
		u64 r = random(state);
		if (r >= threshold)
			return r % bound;
	}
}
