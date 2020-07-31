#pragma once

#include <stdint.h>

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))
#define TO_STRING(x) #x
#define FMOD(x, v) (f32) (((i32)(x)) % v + ((x) - (i32)(x)))
#define KB(x) (i64)1024 * (i64)x
#define MB(x) (i64)1024 * KB(x)
#define GB(x) (i64)1024 * MB(x)
#define nullptr ((void*) 0)

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) > (y)) ? (y) : (x))

#define TOKB(x) ((f64) x) / 1024
#define TOMB(x) ((f64) TOKB(x)) / 1024
#define TOGB(x) ((f64) TOMB(x)) / 1024

#if defined(_MSC_VER)
#define force_inline __forceinline
#else
#define force_inline static inline __attribute((always_inline))
#endif

#define PRINT_ONES(func, msg) { static i8 flag = 1; if (flag) { flag = 0; func(msg); } }
#define PRINT_ONESF(func, format, ...) { static i8 flag = 1; if (flag) { flag = 0; func(format, ##__VA_ARGS__); } }
#define PRINT_ONES3(func, msg, out) { static i8 flag = 1; if (flag) { flag = 0; func(msg, out); } }
