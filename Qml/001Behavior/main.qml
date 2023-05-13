import QtQuick 2.14
import QtQuick.Window 2.14

//实现Qml 抽屉的一种方式。
Window {
  visible: true
  width: 640
  height: 480
  title: qsTr("Hello World")

 Rectangle{
 id:rect
 width:400
 color:"gray"
 height: parent.height

  //速度慢到1K Behavior 动画
  Behavior on width {  NumberAnimation{duration: 1000}}
 }

 MouseArea{
 anchors.fill: parent
 onClicked: rect.width=100
 }
}
