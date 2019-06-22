#ifndef FANCY_H
#define FANCY_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <assert.h>
//@portability: this is needed on windows for some reason, idk why
#ifndef static_assert
# define static_assert _Static_assert
#endif


/// BEGIN type definitions {
typedef uint8_t u8;
typedef int8_t i8;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint64_t u64;
typedef int64_t i64;
#ifndef __SIZEOF_INT128__
# error Need 128-bit numbers.
#endif
typedef __uint128_t u128;
typedef __int128_t i128;
static_assert(sizeof(i128) == 16 && sizeof(u128) == 16, "__(u)int128 is not 128 bits??");

typedef float f32;
typedef double f64;
static_assert(sizeof(f32) == 4, "float is not 32 bits");
static_assert(sizeof(f64) == 8, "double is not 64 bits");

typedef size_t usz;
#ifdef _MSC_VER
# include <BaseTsd.h>
typedef SSIZE_T isz;
#else
# include <sys/types.h>
typedef ssize_t isz;
#endif

// normal types are now illegal
#define t_bad(T) static_assert(false, "Can't use " #T); T
//@cleanup: is it justified to outlaw char?  Maybe it should be used for strings?  Or we should make a typedef for strings above?
#define short t_bad(short)
#define int t_bad(int)
#define unsigned t_bad(unsigned)
#define signed t_bad(signed)
#define long t_bad(long)
#define float t_bad(float)
#define double t_bad(double)
#define size_t t_bad(size_t)
#define ssize_t t_bad(ssize_t)
#undef t_bad
/// END type definitions }


/// BEGIN replacements for standard c constructs and functions {
#define loop while(true)
#define cast(T) (T)

void *alloc(usz sz);
#define malloc(...) malloc(__VA_ARGS__),static_assert(false, "Can't use malloc")
#define calloc(...) calloc(__VA_ARGS__),static_assert(false, "Can't use calloc")
/// END replacements for standard c constructs and functions }


//*randomness*
typedef struct {
	u128 state, inc;
} RngState;

u64 random(RngState *state);
u64 rnb(RngState *state, u64 bound);
void seed_random(RngState *state, u128 initstate, u128 initseq);
// [min, max)
// function because if it were a macro, then 'min' would appear twice, and its side effects—if any—would occur twice
inline u64 rnr(RngState *state, u64 min, u64 max) {
	return rnb(state, max - min) + min;
}

#endif //FANCY_H
