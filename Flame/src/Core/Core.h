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

#ifdef FL_ENABLE_ASSERTS
	#define FL_ASSERT(x, ...) { if(!(x)) { FL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FL_CORE_ASSERT(x, ...) { if(!(x)) { FL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FL_ASSERT(x, ...)
	#define FL_CORE_ASSERT(x, ...)
#endif 

#define  BIT(x) (1 << (x))// 这个宏用于定义位掩码，通常用于事件分类等需要使用位运算的场景