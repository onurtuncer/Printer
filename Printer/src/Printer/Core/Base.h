#pragma once

#include <memory>

#ifdef PRINTER_DEBUG
	#include <signal.h>
	#define PRINTER_DEBUGBREAK() raise(SIGTRAP)
	#define PRINTER_ENABLE_ASSERTS
#endif

#define PRINTER_EXPAND_MACRO(x) x
#define PRINTER_STRINGIFY_MACRO(x) #x

#define BIT(x) (1u << x)

#define PRINTER_BIND_EVENT_FN(fn) std::bind(&##fn, this, std::placeholders::_1)

#include "Log.h"
#include "Assert.h"