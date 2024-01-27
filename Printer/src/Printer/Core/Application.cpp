#include <chrono>
#include <sstream>
#include <thread>
#include "Application.h"
#include "Base.h"

namespace Printer {

  Application* Application::s_Instance = nullptr;

  Application::Application(int& argc, char** argv, ApplicationSpecification spec) 
    : QGuiApplication(argc, argv), m_ApplicationSpecification(spec) {

    PRINTER_CORE_ASSERT(!s_Instance, "Application already exists!");
	  s_Instance = this;
    Initialize();
  }

  Application::~Application() {

    Shutdown();
    s_Instance = nullptr;
  }

  bool Application::Initialize() {

    m_SignalHandler.SetupSignalHandlers();
    auto url = m_ApplicationSpecification.MainWindowUrl;

    m_QmlAppEngine = new QQmlApplicationEngine();
    m_RootContext = m_QmlAppEngine->rootContext();

    QObject::connect(
        m_QmlAppEngine, &QQmlApplicationEngine::objectCreated,
        this, [url](QObject *obj, const QUrl &objUrl)
        {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
  
    m_QmlAppEngine->load(url);

    if (m_QmlAppEngine->rootObjects().isEmpty()) {
      PRINTER_CRITICAL("[UI::Application] QML engine root object is empty, terminating program!..");
      return false;
    }

    // Initialize pin controller

    return true;
  }

  void Application::Shutdown() {

    delete m_QmlAppEngine;
  }

} 