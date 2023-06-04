import QtQuick 2.12
import QtQuick.Controls 2.13
import QtQuick.Window 2.12
import QtQuick.Shapes 1.14
Window {
    width: 800
    height: 480
    visible: true
    title: qsTr("Qt基于Qml任意圆角矩形定制")
    color:"white"

    Shape {
        width: 200
        height: 150
        anchors.centerIn: parent
        antialiasing: true
        ShapePath {
            strokeWidth: 4
            strokeColor: "red"

            strokeStyle: ShapePath.DashLine
            dashPattern: [ 1, 4 ]
            startX: 40; startY: 40
            PathLine { x: 180; y: 130 }
            PathLine { x: 20; y: 130 }
            PathLine { x: 20; y: 20 }
        }
    }
}
