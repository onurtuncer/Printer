#include "Log.h"

namespace Printer {

  std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
  std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

  void Log::Initialize() {

    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_CoreLogger = spdlog::stdout_color_mt("Core Logger");
    s_CoreLogger->set_level(spdlog::level::trace);
    
    s_ClientLogger = spdlog::stdout_color_mt("Client Logger");
    s_ClientLogger->set_level(spdlog::level::trace);    
  }

  void Log::Shutdown() {

    s_ClientLogger.reset();
    s_CoreLogger.reset();
    spdlog::drop_all();
  }

}