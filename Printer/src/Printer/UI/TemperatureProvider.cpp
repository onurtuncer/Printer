// temperatureprovider.cpp
#include "temperatureprovider.h"
#include <QDebug>

TemperatureProvider::TemperatureProvider(QObject *parent)
    : QObject(parent),
      bedSerialPort(ioContext),
      nozzleSerialPort(ioContext),
      ioContextThread([this] { ioContextThreadFunction(); }),
      strand(ioContext.get_executor()),
      readingBedTemperature(false),
      readingNozzleTemperature(false),
      bedTemperature(0.0),
      nozzleTemperature(0.0)
{
    // Initialize and open the bed serial port (update with your bed serial port parameters)
    bedSerialPort.open("/dev/ttyUSB0");
    bedSerialPort.set_option(boost::asio::serial_port_base::baud_rate(9600));

    // Initialize and open the nozzle serial port (update with your nozzle serial port parameters)
    nozzleSerialPort.open("/dev/ttyUSB1");
    nozzleSerialPort.set_option(boost::asio::serial_port_base::baud_rate(9600));
}

TemperatureProvider::~TemperatureProvider()
{
    stopReadingTemperatures();

    if (ioContextThread.joinable()) {
        ioContextThread.join();
    }

    // Close the serial ports on destruction
    bedSerialPort.close();
    nozzleSerialPort.close();
}

void TemperatureProvider::startReadingTemperatures()
{
    if (!readingBedTemperature) {
        readingBedTemperature = true;

        // Start the asynchronous read operation for bed temperature
        boost::asio::async_read(bedSerialPort,
                                boost::asio::buffer(bedBuffer, sizeof(bedBuffer)),
                                strand.wrap([this](const boost::system::error_code& error, std::size_t bytesRead) {
            handleReadBed(error, bytesRead);
        }));
    }

    if (!readingNozzleTemperature) {
        readingNozzleTemperature = true;

        // Start the asynchronous read operation for nozzle temperature
        boost::asio::async_read(nozzleSerialPort,
                                boost::asio::buffer(nozzleBuffer, sizeof(nozzleBuffer)),
                                strand.wrap([this](const boost::system::error_code& error, std::size_t bytesRead) {
            handleReadNozzle(error, bytesRead);
        }));
    }
}

void TemperatureProvider::stopReadingTemperatures()
{
    if (readingBedTemperature) {
        readingBedTemperature = false;
        ioContext.stop();
    }

    if (readingNozzleTemperature) {
        readingNozzleTemperature = false;
        ioContext.stop();
    }
}

void TemperatureProvider::ioContextThreadFunction()
{
    ioContext.run();
}

void TemperatureProvider::handleReadBed(const boost::system::error_code& error, std::size_t bytesRead)
{
    if (!error) {
        // Parse the received data and update bed temperature value
        // The logic here depends on the format of the data received from the bed serial port
        // For simplicity, let's assume the data is a single temperature value
        QString data(bedBuffer, bytesRead);
        bool conversionSuccess;
        qreal newBedTemperature = data.toDouble(&conversionSuccess);

        if (conversionSuccess) {
            if (newBedTemperature != bedTemperature) {
                bedTemperature = newBedTemperature;
                emit bedTemperatureChanged(bedTemperature);
            }
        } else {
            qDebug() << "Failed to convert bed temperature value.";
        }

        // Continue reading data asynchronously
        boost::asio::async_read(bedSerialPort,
                                boost::asio::buffer(bedBuffer, sizeof(bedBuffer)),
                                strand.wrap([this](const boost::system::error_code& e, std::size_t bytes) {
            handleReadBed(e, bytes);
        }));
    } else {
        qDebug() << "Error reading bed temperature: " << error.message();
        // Handle error appropriately, e.g., stopReadingTemperatures()
    }
}

void TemperatureProvider::handleReadNozzle(const boost::system::error_code& error, std::size_t bytesRead)
{
    if (!error) {
        // Parse the received data and update nozzle temperature value
        // The logic here depends on the format of the data received from the nozzle serial port
        // For simplicity, let's assume the data is a single temperature value
        QString data(nozzleBuffer, bytesRead);
        bool conversionSuccess;
        qreal newNozzleTemperature = data.toDouble(&conversionSuccess);

        if (conversionSuccess) {
            if (newNozzleTemperature != nozzleTemperature) {
                nozzleTemperature = newNozzleTemperature;
                emit nozzleTemperatureChanged(nozzleTemperature);
            }
        } else {
            qDebug() << "Failed to convert nozzle temperature value.";
        }

        // Continue reading data asynchronously
        boost::asio::async_read(nozzleSerialPort,
                                boost::asio::buffer(nozzleBuffer, sizeof(nozzleBuffer)),
                                strand.wrap([this](const boost::system::error_code& e, std::size_t bytes) {
            handleReadNozzle(e, bytes);
        }));
    } else {
        qDebug() << "Error reading nozzle temperature: " << error.message();
        // Handle error appropriately, e.g., stopReadingTemperatures()
    }
}
