#pragma once 

namespace Printer::Temperature{

class Controller{

  public:
    explicit Controller();
    virtual  ~Controller();

  private:
    double m_SetPoint();

};


}
