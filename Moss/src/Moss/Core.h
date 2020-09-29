#pragma once


#ifdef MOSS_PLATFORM_WINDOWS

	#ifdef MOSS_BUILD_DLL
		#define MOSS_API __declspec(dllexport)
	#else
		#define MOSS_API __declspec(dllimport)
	#endif

#else

	#error Moss only support Windows!

#endif