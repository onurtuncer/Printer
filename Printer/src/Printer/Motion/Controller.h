#pragma once

#include "Interpreter.h"

namespace Printer::Motion{

  class Controller{

    public:
      explicit Controller();
      virtual ~Controller();

      HomeAllAxes();
      PausePrinting();

    private:

      bool m_IsPaused{false};
      
   


  }



}
