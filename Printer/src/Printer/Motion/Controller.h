#pragma once

#include "Interpreter.h"
#include "Stepper.h"

namespace Printer::Motion{

  class Controller{

    public:
      explicit Controller();
      virtual ~Controller();

      HomeAllAxes();
      PausePrinting();

    private:
      typedef std::string::const_iterator Iterator;
      RS274NGCGrammar<Iterator> m_Parser;

      bool m_IsPaused{false};
      


  }



}
