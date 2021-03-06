#pragma once

#include <memory.h>

#ifdef MOSS_PLATFORM_WINDOWS

	#ifdef MS_DYNAMIC_LINK
		#ifdef MOSS_BUILD_DLL
			#define MOSS_API   __declspec(dllexport)
		#else
			#define MOSS_API __declspec(dllimport)
		#endif
	#else
		#define MOSS_API
	#endif

#else

	#error Moss only support Windows!

#endif


#ifdef MS_DEBUG
	#define MS_ENABLE_ASSERT
#endif


#ifdef MS_ENABLE_ASSERT
	#define MS_ASSERT(x, ...)		{if(!(x)) {MS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}  //debugbreak可以在调试的时候，断言失败做一个断点
	#define MS_CORE_ASSERT(x, ...){if(!(x)) {MS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define MS_ASSERT(x, ...)	
	#define MS_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)

#define MS_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)



namespace Moss {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;


}