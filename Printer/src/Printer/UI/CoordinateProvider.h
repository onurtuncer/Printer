#pragma once

#include <QObject>
#include <QTimer>

namespace Printer{

class Motion::Controller;

namespace UI{

class CoordinateProvider : public QObject
{
    Q_OBJECT

public:
    CoordinateProvider(MotionController *motionController, QObject *parent = nullptr);

    qreal getXCoordinate() const;
    qreal getYCoordinate() const;
    qreal getZCoordinate() const;

public slots:
    void startUpdatingCoordinates();
    void stopUpdatingCoordinates();

private slots:
    void updateCoordinates();

signals:
    void xCoordinateChanged(qreal x);
    void yCoordinateChanged(qreal y);
    void zCoordinateChanged(qreal z);

private:
    MotionController *motionController;
    QTimer updateTimer;
};

}

}


