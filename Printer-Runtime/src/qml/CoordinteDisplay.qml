// CoordinateDisplay.qml
import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: 200
    height: 100

    Text {
        id: coordinatesText
        text: "X: 0 mm\nY: 0 mm\nZ: 0 mm"
        anchors.fill: parent
        font.pixelSize: 16
        color: "black"
    }

    Connections {
        target: printerCoordinatesUpdater // Replace with the actual object emitting signals

        onXCoordinateChanged: {
            coordinatesText.text = "X: " + xCoordinate.toFixed(2) + " mm\nY: " + yCoordinate.toFixed(2) + " mm\nZ: " + zCoordinate.toFixed(2) + " mm"
        }

        onYCoordinateChanged: {
            coordinatesText.text = "X: " + xCoordinate.toFixed(2) + " mm\nY: " + yCoordinate.toFixed(2) + " mm\nZ: " + zCoordinate.toFixed(2) + " mm"
        }

         onZCoordinateChanged: {
            coordinatesText.text = "X: " + xCoordinate.toFixed(2) + " mm\nY: " + yCoordinate.toFixed(2) + " mm\nZ: " + zCoordinate.toFixed(2) + " mm"
        }

    }
}
