﻿#pragma once

#include "Platform.h"

#ifdef ZS_WINOS		//for windows

#ifdef _WINDLL
#define XDLL _declspec(dllexport)
#else
#define XDLL _declspec(dllimport)
#endif

#else		// for linux

#define XDLL

#endif

#define ZLIB_DLL

typedef unsigned int uint;
#ifdef _MSC_VER
typedef __int8  int8;
typedef __int16 int16;
typedef __int32 int32;
typedef __int64 int64;

typedef unsigned __int8  uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;
#else
typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
#endif
