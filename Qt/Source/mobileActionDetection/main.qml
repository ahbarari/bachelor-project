
import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtSensors 5.9
import QtQuick.Window 2.2
import Qt.labs.settings 1.0
import com.socket 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property int cntr_gyros: 0
    property int cntr_acc: 0

    property var date
    property var startCaptureTime

    ClientSocket{
        id: socket

        //-- QString msg --//
        onMsg: {
            txt_error.text += msg + "\n"
        }
    }

    Settings{
            id: setting

            property alias ipAddress: txt_ip.text

        }

    //-- tools --//
    ColumnLayout{
        anchors.fill: parent

        //-- connect ip --//
        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: btn_connect.height * 1.5

            RowLayout{
                anchors.fill: parent

                Item{Layout.fillWidth: true}

                //-- connect button --//
                Button{
                    id: btn_connect

                    property bool isConnect: false

                    text: isConnect ? "disconnect" : "connect"

                    onClicked:{
                        if(!isConnect){

                            isConnect = socket.connectToIp(txt_ip.text)
                            cntr_acc= 0;
                            cntr_gyros= 0;
                        }
                        else{
                            accel.active = false
                            gyroscope.active = false
                            orient.active = false

                            socket.disConnect()
                            isConnect = false
                        }

                    }
                }

                TextField{
                    id: txt_ip

                    text: "192.168.1.104"
                    selectByMouse: true
                }

                Item{Layout.fillWidth: true}
            }
        }

        //-- data rate --//
        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: btn_connect.height * 1.5

            RowLayout{
                anchors.fill: parent

                Item{Layout.fillWidth: true}

                Label{
                    text: "data rate:"
                }

                //-- dataRate --//
                TextField{
                    id: txt_dataRate

                    text: "100"
                    selectByMouse: true
                }

                Item{Layout.fillWidth: true}
            }
        }


        //-- active Buttons --//
        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: btn_connect.height * 1.5

            RowLayout{
                anchors.fill: parent

                Item{Layout.fillWidth: true}

                Button{
                    id: btn_active

                    text: accel.active ? "deactivate Accelerometer/gyroscope" : "activate Accelerometer/gyroscope"
                    onClicked: {
                        var d = new Date()
                        startCaptureTime = d.getTime();
                        console.log("start date = " + startCaptureTime)
                        gyroscope.active = !gyroscope.active
                        accel.active = !accel.active
                    }
                }

                Rectangle{
                    Layout.preferredHeight: btn_active.height * 0.5
                    Layout.preferredWidth: height
                    radius: width * 0.5
                    border.color: "black"
                    border.width: 1
                    smooth: true

                    color:  accel.active ? "Green" : "Red"
                }

                Item{Layout.fillWidth: true}

            }

        }


        //-- sensor data presenter --//
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            Label{
                id: lbl_data
                anchors.centerIn: parent
                text: ""
            }

            Label{
                id: lbl_gyr
                anchors.centerIn: parent
                anchors.verticalCenterOffset: 100
                text: ""
            }

            Label{
                id: lbl_orri
                visible: false
                anchors.centerIn: parent
                anchors.verticalCenterOffset: 200
                text: ""
            }

            TextArea {
                id: txt_error
                anchors.centerIn: parent
                anchors.verticalCenterOffset: 200
                anchors.fill: parent
                text: qsTr("")
            }
        }
    }


    Accelerometer {
        id: accel

        property string buffer: "0_0_0"

        dataRate: 100 //parseInt(txt_dataRate.text)

        active: false
        alwaysOn: true

        onReadingChanged: {

            lbl_data.text = accel.reading.x + "\n" + accel.reading.y + "\n" + accel.reading.z
            var now = new Date()
            if(accel.active) socket.sendData(
                                 "#" + "ACC" + "_" +
                                 (now.getTime() - startCaptureTime) + "_" +
                                 accel.reading.x + "_" +
                                 accel.reading.y + "_" +
                                 accel.reading.z
                                 )

        }

    }

    Gyroscope {
        id: gyroscope
        dataRate: 100//parseInt(txt_dataRate.text)

        active: false
        alwaysOn: true

        onReadingChanged: {

            lbl_gyr.text = gyroscope.reading.x + "\n" + gyroscope.reading.y + "\n" + gyroscope.reading.z
            var now = new Date()
            if(gyroscope.active) socket.sendData(
                                     "#" + "GYR" + "_" +
                                     (now.getTime() - startCaptureTime) + "_" +
                                     gyroscope.reading.x + "_" +
                                     gyroscope.reading.y + "_" +
                                     gyroscope.reading.z
                                     )

        }

    }

}
