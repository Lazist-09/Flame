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

#define  BIT(x) (1 << (x))// 这个宏用于定义位掩码，通常用于事件分类等需要使用位运算的场景