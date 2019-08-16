#pragma once

#ifdef HEIST_PLATFORM_WINDOWS
	#ifdef HEIST_BUILD_DLL
		#define HEIST_API __declspec(dllexport)
	#else
		#define HEIST_API __declspec(dllimport)
	#endif
#else
	#error Engine only supports Windows
#endif