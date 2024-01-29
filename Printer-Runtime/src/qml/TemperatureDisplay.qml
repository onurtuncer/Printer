// TemperatureDisplay.qml
import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: 300
    height: 200

    Text {
        anchors.centerIn: parent
        text: "Bed Temperature: " + temperatureProvider.bedTemperature.toFixed(2) + " °C"
        font.pixelSize: 16
    }

    Text {
        anchors {
            top: parent.top
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }
        text: "Nozzle Temperature: " + temperatureProvider.nozzleTemperature.toFixed(2) + " °C"
        font.pixelSize: 16
    }

    Connections {
        target: temperatureProvider

        onBedTemperatureChanged: {
            // Update the displayed bed temperature when it changes
            bedTemperatureText.text = "Bed Temperature: " + temperature.toFixed(2) + " °C";
        }

        onNozzleTemperatureChanged: {
            // Update the displayed nozzle temperature when it changes
            nozzleTemperatureText.text = "Nozzle Temperature: " + temperature.toFixed(2) + " °C";
        }
    }
}
