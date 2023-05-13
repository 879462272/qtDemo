import QtQuick 2.12
import QtQuick.Window 2.12

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Window 2.12

/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       main.qml
 * @brief      Qml 讲究的是树级分布，只有一个根对象，然后分布下去 ，事件穿透主要是propagateComposedEvents 和accepted 这两个APi
 *
 * @author     xxx<xxx@xxx.com>
 * @date       2023/05/13
 * @history
 *****************************************************************************/
Window {
    visible: true
    width: 640
    height: 480

    MouseArea{
        anchors.fill: parent
        onPressed: console.log("~root pressed")
        onClicked: console.log("~root clicked")
    }

    //item的层级在root之上（因为他写在mousearea的后面，又是同级的）
    Rectangle{
        width: 200
        height: 200
        color: "green"

        MouseArea{
            anchors.fill: parent
            //是否传递到被覆盖的MouseArea
           propagateComposedEvents: true

           // onPressed:{console.log("item"); mouse.accepted=false}
        }
    }
}
