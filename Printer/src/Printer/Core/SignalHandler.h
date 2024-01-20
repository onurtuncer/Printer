#pragma once

#include <stdexcept>

namespace Printer {

    using std::runtime_error;
    
    class SignalException : public runtime_error {
      public:
        SignalException(const std::string& message) : std::runtime_error(message) {/*empty*/}
    };
    
    class SignalHandler {
      protected:
        static bool m_bGotExitSignal;
        static bool m_bGotStopSignal;
      public:
        explicit SignalHandler();
        virtual ~SignalHandler();
        static bool GotExitSignal();
        static bool GotStopSignal();
        static void SetExitSignal(bool bExitSignal);
        static void SetStopSignal(bool bStopSignal);
        void SetupSignalHandlers();
        static void ExitSignalHandler(int ignored);
        static void StopSignalHandler(int ignored);
    };

} 