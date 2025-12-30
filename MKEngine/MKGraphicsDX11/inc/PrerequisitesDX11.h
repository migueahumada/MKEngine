
#pragma once

#include <stdint.h>
#include <string>
#include <array>
#include <map>
#include <memory>
#include <vector>

//**********************MACROS***************************
#define NODISCARD_MSG "This value is not being used!"
#define NODISCARD [[nodiscard(NODISCARD_MSG)]]

#define SWAPCHAIN_SIZE 2

//**********************DLL export***********************
#if defined(MK_GRAPHICS_DX11)
#define MK_DX11_API __declspec(dllexport)
#else
#define MK_DX11_API __declspec(dllimport)
#endif

#define SAFE_RELEASE(p) { if(p){p->Release(); p = nullptr;} }



//***********************INT types***********************
using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

//***********************STL***********************
using String = std::string;

template<typename K, typename V>
using Map = std::map<K, V>;

template<class T, size_t N>
using Array = std::array<T, N>;

template<class T>
using Vector = std::vector<T>;

//***********************SMRT PTRS***********************
template <typename T>
using UPtr = std::unique_ptr<T>;

template <typename T>
using SPtr = std::shared_ptr<T>;

template<typename T>
using WPtr = std::weak_ptr<T>;

using std::make_shared;
using std::make_unique;

