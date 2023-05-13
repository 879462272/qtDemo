import QtQuick 2.14
import QtQuick.Window 2.14

//实现Qml 抽屉的一种方式。
Window {
  id:root
  visible: true
  width: 640
  height: 480
  title: qsTr("Model")
  property var falg: true
 Rectangle{

 id:rect
 width:400
 color:"gray"
 height: parent.height
 clip:true

  //速度慢到1K Behavior 动画
  Behavior on width {  NumberAnimation{duration: 400}}
 }

 MouseArea{
 anchors.fill: parent
 onClicked: rect.width50
 }

 Rectangle{

   //opacity: 0
   width: 40;height: 40;
   clip: true
   radius: 20
   color: "white"
   anchors.verticalCenter:rect.verticalCenter
   anchors.right: rect.right
   anchors.rightMargin: -20

   MouseArea{
   anchors.fill: parent
   onClicked:{ root.falg?rect.width=400:rect.width=50;root.falg=!root.falg}
   }

 }
}