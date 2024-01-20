#pragma once

#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/fmt/ostr.h"

namespace Printer {
  
    class Log final {
      public:

        static void Initialize();
        static void Shutdown();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){
          return s_CoreLogger;
        };
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger(){
          return s_ClientLogger;
        };

        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
        
      private:

    };
}

#define PRINTER_CORE_CRITICAL(...) ::Printer::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define PRINTER_CORE_ERROR(...)    ::Printer::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PRINTER_CORE_WARN(...)     ::Printer::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PRINTER_CORE_INFO(...)     ::Printer::Log::GetCoreLogger()->info(__VA_ARGS__)

#define PRINTER_CRITICAL(...)      ::Printer::Log::GetClientLogger()->critical(__VA_ARGS__)
#define PRINTER_ERROR(...)         ::Printer::Log::GetClientLogger()->error(__VA_ARGS__)
#define PRINTER_WARN(...)          ::Printer::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PRINTER_INFO(...)          ::Printer::Log::GetClientLogger()->info(__VA_ARGS__)

#ifdef DEBUG

#define PRINTER_CORE_TRACE(...)  ::Printer::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PRINTER_TRACE(...)       ::Printer::Log::GetClientLogger()->trace(__VA_ARGS__)

#else
#define PRINTER_CORE_TRACE
#define PRINTER_TRACE

#endif