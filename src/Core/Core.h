#pragma once

#ifdef FL_PLATFORM_WINDOWS
	#ifdef FLAME_BUILD_DLL
		#define FL_API __declspec(dllexport)
	#else
		#define FL_API __declspec(dllimport)
	#endif
#else
	#error Flame only supports Windows!
#endif