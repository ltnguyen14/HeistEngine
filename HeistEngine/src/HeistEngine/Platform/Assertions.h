#pragma once
#include "Core/Log/Log.h"

#ifdef HEIST_PLATFORM_WINDOWS
	#ifdef HS_ENABLE_ASSERTS
		#define HS_ASSERT(x, ...) { if(!(x)) { HS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
		#define HS_CORE_ASSERT(x, ...) { if(!(x)) { HS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#else
		#define HS_ASSERT(x, ...)
		#define HS_CORE_ASSERT(x, ...)
	#endif
#else
	#error Engine only supports Windows
#endif