
#include "Coordinateprovider.h"
#include "Motion/Controller.h" // 

namespace Printer::UI{

CoordinateProvider::CoordinateProvider(MotionController *motionController, QObject *parent)
    : QObject(parent),
      motionController(motionController)
{
    connect(&updateTimer, &QTimer::timeout, this, &CoordinateProvider::updateCoordinates);
}

qreal CoordinateProvider::getXCoordinate() const{
  
    return motionController->getXCoordinate();
}

qreal CoordinateProvider::getYCoordinate() const{
    return motionController->getYCoordinate();
}

qreal CoordinateProvider::getZCoordinate() const{
  
    return motionController->getZCoordinate();
}

void CoordinateProvider::StartUpdatingCoordinates(){
  
    // Start the timer to update coordinates every 50 ms
    updateTimer.start(50);
}

void CoordinateProvider::StopUpdatingCoordinates(){
    // Stop the timer
    updateTimer.stop();
}

void CoordinateProvider::updateCoordinates()
{
    // Ask MotionController for updated coordinates
    setXCoordinate(motionController->getXCoordinate());
    setYCoordinate(motionController->getYCoordinate());
    setZCoordinate(motionController->getZCoordinate());
}

