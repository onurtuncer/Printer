#include <Printer.h>
#include <csignal>
#include <stdlib.h>

int main (int argc, char** argv) {

    int iret;
    Printer::Log::Initialize();
    Printer::ApplicationSpecification spec;

    spec.Name = "Printer Application";
  
    const QUrl mainWindowUrl = QUrl(QStringLiteral("qrc:/qml/MainWindow.qml"));
    spec.MainWindowUrl = mainWindowUrl;

    PRINTER_INFO("Starting application...");
	
    Printer::Application* app = new Printer::Application(argc, argv, spec);

    try{     
        iret = app->exec();
    }
    catch (Printer::SignalException& e){
        PRINTER_CRITICAL("Signal exception caught!...");
        iret = EXIT_FAILURE;
    }
    catch(...){
        PRINTER_CRITICAL("Unknown exception caught!...");
        iret = EXIT_FAILURE;
    }

    if (iret != 0) {PRINTER_CRITICAL("Application quitted unexpectedly!...");}
    else {PRINTER_INFO("Application quitted normally...");}

    delete app;
    return (iret);
}