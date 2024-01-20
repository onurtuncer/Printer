#include <signal.h>
#include <errno.h>

#include "SignalHandler.h"

namespace Printer {

    bool SignalHandler::m_bGotExitSignal = false;
    bool SignalHandler::m_bGotStopSignal = false;

    SignalHandler::SignalHandler() {}
    SignalHandler::~SignalHandler(){}

    bool SignalHandler::GotExitSignal() {
        return m_bGotExitSignal;
    }

    void SignalHandler::SetExitSignal(bool bExitSignal) {
        m_bGotExitSignal = bExitSignal;
    }

    void SignalHandler::ExitSignalHandler(int ignored) {
        m_bGotExitSignal = true;
    }

    bool SignalHandler::GotStopSignal() {
      return m_bGotStopSignal;
    }

    void SignalHandler::SetStopSignal(bool bStopSignal)  {
      m_bGotStopSignal = true;
    }

    void SignalHandler::StopSignalHandler(int ignored) {
      m_bGotStopSignal = true;
    }

    void SignalHandler::SetupSignalHandlers()  {

        if (signal((int) SIGINT,  SignalHandler::ExitSignalHandler) == SIG_ERR)
           {
            throw SignalException("Error setting up signal handlers");
        }


    }

} 