#pragma once
#include "cstdint"

#define HS_ARRAY_COUNT(arr) (sizeof(arr) / sizeof(arr[0]))
#define BIT(x) (1 << x)
#define PI 3.14159265

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uintmax_t uintmax;

typedef float real32;
typedef double real64;

// CONSTANTS

constexpr auto Pi = 3.14159265359f;