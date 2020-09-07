import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import com.Server 1.0
import com.Python 1.0

Window {
    id: root

    property int _ACTION_UP   : 1
    property int _ACTION_LEFT : 2
    property int _ACTION_RIGHT: 3
    property int _ACTION_DOWN : 4

    property int current_action: 0
    onCurrent_actionChanged: {
        print("current action is " , current_action)
    }

    visible: true
    width: 750
    height: 480
    title: qsTr(" ")

    property real radiansToDegrees : 360.0 / Math.PI

    //--posX movement for animation --//
    property int animXdiff: 40

    Server{
        id: server
        serverStatus: false

        //-- qreal x, qreal y, qreal z --//
        onGyroscopeData: {

            var m_x = x.toFixed(2) / 300
            var m_y = y.toFixed(2) / 300
            var m_z = z.toFixed(2) / 300
            lbl_x.text = "x: " + x
            lbl_y.text = "y: " + y
            lbl_z.text = "z: " + z
        }

        //-- QString fileUrl --//
        onCaptureAction: {

            current_action = 0

            //-- set action file address --//
            py.setActionFileUrl(fileUrl)

            //-- detect action --//
            py.readFromPython()
        }
    }

    //-- python section --//
    Python{
        id: py

        //-- QString action --//
        onDetectAction: {
            if(action.indexOf("UP") !== -1){
                current_action = _ACTION_UP
                anim_up.restart()
            }
            else if(action.indexOf("DOWN") !== -1){
                current_action = _ACTION_DOWN
                anim_down.restart()
            }
            else if(action.indexOf("RIGHT") !== -1){
                current_action = _ACTION_RIGHT
                anim_right.restart()
            }
            else if(action.indexOf("LEFT") !== -1){
                current_action = _ACTION_LEFT
                anim_left.restart()
            }
        }
    }

    Component.onCompleted: {
        var ips = server.getServerIp()
        var list_ip = ips.split('_')
        print("ipos: " + list_ip)
        for(var i=0; i<list_ip.length; i++){

            var secs = list_ip[i].split('.')

            if(secs[3] === "1") continue

            lbl_ip.text = lbl_ip.text + list_ip[i]
            if(i !== list_ip.length-1) lbl_ip.text = lbl_ip.text + " , "
        }
    }

    //-- body --//
    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 5

        //-- tools --//
        Rectangle{
            Layout.fillWidth: true
            Layout.preferredHeight: btn_startSewrver.implicitHeight * 2

            layer.enabled: true
            layer.effect: DropShadow {
                transparentBorder: true
                horizontalOffset: 1//8
                verticalOffset: 1//8
                color: "#80000000"
                spread: 0.0
                samples: 17
                radius: 12
            }

            RowLayout{
                anchors.fill: parent

                //-- ip section --//
                Item{
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    RowLayout{
                        anchors.fill: parent
                        anchors.margins: 3

                        Image {
                            source: "qrc:/Images/ips.png"

                            fillMode: Image.PreserveAspectFit
                            sourceSize.width: parent.height * 0.5
                            sourceSize.height: parent.height * 0.5
                        }

                        Label{
                            id: lbl_ip
                            text: ""
                        }
                        Item{ Layout.fillWidth: true }
                    }


                }

                //-- start/stop server --//
                Button{
                    id: btn_startSewrver
                    text: "Start"
                    onClicked: {

                        if(!server.serverStatus){

                            server.startServer()
                            btn_startSewrver.text = "Stop"
                        }
                        else{
                            server.stopServer()
                            btn_startSewrver.text = "Start"
                        }

                    }
                }

                //-- image for server status --//
                Image {
                    id: img_server
                    source: server.serverStatus ? "qrc:/Images/server_on.png" : "qrc:/Images/server_off.png"
                    //                    Layout.fillHeight: true
                    fillMode: Image.PreserveAspectFit
                    sourceSize.width: parent.height * 0.8
                    sourceSize.height: parent.height * 0.8

                }

                //-- server status text --//
                Label{
                    id: lbl_serverStatus
                    text: server.serverStatus ? "Listening..." : "Server closed."
                }

                //-- set python script --//
                Item{
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    RowLayout{
                        anchors.fill: parent
                        anchors.margins: 3

                        Item{Layout.fillWidth: true}

                        Button{
                            Layout.preferredWidth: implicitHeight
                            text: ""
                            icon.source: "qrc:/Images/folder.svg"

                            ToolTip.delay: 600
                            ToolTip.timeout: 5000
                            ToolTip.visible: hovered
                            ToolTip.text: qsTr("set python main.py run script text")

                            onClicked: {
                                popup.open()
                            }
                        }
                    }

                }

            }

        }

        //-- action images --//
        Item{
            Layout.fillWidth: true
            Layout.fillHeight: true

            Rectangle{
                anchors.fill: parent
                anchors.margins: 10
                color: "transparent"
                border{
                    width: 1
                    color: "grey"
                }

                //-- center --//
                Image {
                    source: "qrc:/Images/action/action_center.png"
                    anchors.centerIn: parent
                }

                //-- up --//
                Image {
                    id: img_up
                    source: current_action === _ACTION_UP ? "qrc:/Images/action/action_up_on.png" : "qrc:/Images/action/action_up_off.png"
                    anchors.centerIn: parent

                    SequentialAnimation{
                        id: anim_up
                        NumberAnimation {
                            target: img_up
                            property: "anchors.verticalCenterOffset"
                            from: 0; to: -animXdiff;
                            duration: 200
                            easing.type: Easing.InOutQuad
                        }
                        NumberAnimation {
                            target: img_up
                            property: "anchors.verticalCenterOffset"
                            from: -animXdiff; to: 0;
                            duration: 200
                            easing.type: Easing.InOutQuad
                        }
                    }
                }

                //-- right --//
                Image {
                    id: img_right
                    source: current_action === _ACTION_RIGHT ? "qrc:/Images/action/action_right_on.png" : "qrc:/Images/action/action_right_off.png"
                    anchors.centerIn: parent

                    SequentialAnimation{
                        id: anim_right
                        NumberAnimation {
                            target: img_right
                            property: "anchors.horizontalCenterOffset"
                            from: 0; to: animXdiff;
                            duration: 200
                            easing.type: Easing.InOutQuad
                        }
                        NumberAnimation {
                            target: img_right
                            property: "anchors.horizontalCenterOffset"
                            from: animXdiff; to: 0;
                            duration: 200
                            easing.type: Easing.InOutQuad
                        }
                    }
                }

                //-- left --//
                Image {
                    id: img_left
                    source: current_action === _ACTION_LEFT ? "qrc:/Images/action/action_left_on.png" : "qrc:/Images/action/action_left_off.png"
                    anchors.centerIn: parent

                    SequentialAnimation{
                        id: anim_left

                        NumberAnimation {
                            target: img_left
                            property: "anchors.horizontalCenterOffset"
                            from: 0; to: -animXdiff;
                            duration: 200
                            easing.type: Easing.InOutQuad
                        }
                        NumberAnimation {
                            target: img_left
                            property: "anchors.horizontalCenterOffset"
                            from: -animXdiff; to: 0;
                            duration: 200
                            easing.type: Easing.InOutQuad
                        }
                    }
                }

                //-- down --//
                Image {
                    id: img_down
                    source: current_action === _ACTION_DOWN ? "qrc:/Images/action/action_down_on.png" : "qrc:/Images/action/action_down_off.png"
                    anchors.centerIn: parent

                    SequentialAnimation{
                        id: anim_down

                        NumberAnimation {
                            target: img_down
                            property: "anchors.verticalCenterOffset"
                            from: 0; to: animXdiff;
                            duration: 200
                            easing.type: Easing.InOutQuad
                        }
                        NumberAnimation {
                            target: img_down
                            property: "anchors.verticalCenterOffset"
                            from: animXdiff; to: 0;
                            duration: 200
                            easing.type: Easing.InOutQuad
                        }
                    }
                }

                //-- data --//
                ColumnLayout{
                    visible: false
                    //                    anchors.fill: parent
                    anchors.centerIn: parent
                    spacing: 4

                    Label{
                        id: lbl_x
                        font.pixelSize: 20
                    }

                    Label{
                        id: lbl_y
                        font.pixelSize: 20
                    }

                    Label{
                        id: lbl_z
                        font.pixelSize: 20
                    }
                }

            }

        }

    }

    //-- set python main.py run script --//
    Popup {
        id: popup

        x: root.width/2 - width/2
        y: root.height/2 - height/2
        width: 600
        height: 100
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        RowLayout{
            anchors.fill: parent
            anchors.margins: 5

            TextField{
                id: txt_py_address
                Layout.fillWidth: true
                placeholderText: "python main address"
                selectByMouse: true

                text: "D:/projects/action_detection/bachelor-project/venv/Scripts/python.exe D:/projects/action_detection/bachelor-project/main.py"
            }

            Button{
                text: "set"

                onClicked:{
                    py.setPythonMainScript(txt_py_address.text)
                    popup.close()
                }
            }
        }
    }

}
