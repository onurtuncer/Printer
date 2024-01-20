#pragma once

#include <filesystem>
#include "Base.h"
#include "Log.h"

#ifdef PRINTER_ENABLE_ASSERTS

	#define PRINTER_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { PRINTER##type##ERROR(msg, __VA_ARGS__); PRINTER_DEBUGBREAK(); } }
	#define PRINTER_INTERNAL_ASSERT_WITH_MSG(type, check, ...) PRINTER_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define PRINTER_INTERNAL_ASSERT_NO_MSG(type, check) PRINTER_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", PRINTER_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define PRINTER_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define PRINTER_INTERNAL_ASSERT_GET_MACRO(...) PRINTER_EXPAND_MACRO( PRINTER_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, PRINTER_INTERNAL_ASSERT_WITH_MSG, PRINTER_INTERNAL_ASSERT_NO_MSG) )

	#define PRINTER_ASSERT(...) PRINTER_EXPAND_MACRO( PRINTER_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define PRINTER_CORE_ASSERT(...) PRINTER_EXPAND_MACRO( PRINTER_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define PRINTER_ASSERT(...)
	#define PRINTER_CORE_ASSERT(...)
#endif

