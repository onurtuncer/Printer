#pragma once

#include <QObject>
#include <boost/asio.hpp>
#include <thread>

namespace Printer::UI{

class TemperatureProvider : public QObject{
    Q_OBJECT

public:
    TemperatureProvider(QObject *parent = nullptr);
    ~TemperatureProvider();

public slots:
    void StartReadingTemperatures();
    void StopReadingTemperatures();

signals:
    void bedTemperatureChanged(qreal temperature);
    void nozzleTemperatureChanged(qreal temperature);

private:
    void HandleReadBed(const boost::system::error_code& error, std::size_t bytesRead);
    void HandleReadNozzle(const boost::system::error_code& error, std::size_t bytesRead);
    void IOContextThreadFunction();

    boost::asio::io_context m_IOContext;
    boost::asio::serial_port bedSerialPort;
    boost::asio::serial_port nozzleSerialPort;
    std::thread m_IOContextThread;
    boost::asio::strand<boost::asio::io_context::executor_type> strand;
    char bedBuffer[256]; // Adjust the buffer size accordingly
    char nozzleBuffer[256]; // Adjust the buffer size accordingly
    bool readingBedTemperature;
    bool readingNozzleTemperature;

    qreal bedTemperature;
    qreal nozzleTemperature;
};

}
