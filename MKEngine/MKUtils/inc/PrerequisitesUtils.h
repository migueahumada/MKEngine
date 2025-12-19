#pragma once
#include <stdint.h>

#define NODISCARD_MSG "This value is not being used!"
#define NODISCARD [[nodiscard(NODISCARD_MSG)]]

#if defined(MK_UTILS)
  #define MK_UTILS_API __declspec(dllexport)
#else
  #define MK_UTILS_API __declspec(dllimport)
#endif

using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;
