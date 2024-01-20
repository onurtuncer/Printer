import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 480
    height: 800
    title: "Qt Quick Example"

    Image {
        anchors.centerIn: parent
        source: "images/myimage.png"
    }

    Button {
        text: "Click me!"
        anchors.centerIn: parent

        onClicked: {
            console.log("Button clicked!")
            // Add your button click logic here
        }
    }
}
