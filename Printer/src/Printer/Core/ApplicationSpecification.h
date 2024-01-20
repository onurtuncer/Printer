#pragma once 

#include <string>
#include <QString>
#include <QUrl>

namespace Printer {

  struct ApplicationSpecification {

    std::string     Name;
    std::string     WorkingDirectory;
    QUrl MainWindowUrl = QUrl(QStringLiteral("qrc:/qml/MainWindow.qml"));
  };
} 
