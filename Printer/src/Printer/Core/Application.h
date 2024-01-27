#pragma once 

#include <memory>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ApplicationSpecification.h"
#include "SignalHandler.h"
#include "GPIO/PinController.h"

namespace Printer {

  class Application : public QGuiApplication {
    Q_OBJECT
    
  public:
    explicit Application(int& argc, char** argv, ApplicationSpecification spec);
    virtual ~Application();

    static Application* GetInstance() {return s_Instance;}

    void Shutdown();

  private:
    bool Initialize();
    ApplicationSpecification m_ApplicationSpecification;
    static Application* s_Instance;
  //  std::mutex m_Mutex;
  
  protected:
    SignalHandler m_SignalHandler;

  private:
    QQmlApplicationEngine* m_QmlAppEngine;
    QQmlContext* m_RootContext;
  private:
    std::shared_ptr<PinController> m_PinControllerPtr;
  };
 
} 