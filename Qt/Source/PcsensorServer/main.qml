import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
//import QtQuick3D 1.15
import com.Server 1.0

Window {
    visible: true
    width: 500
    height: 150
    color: "#f5f5f5"
    title: qsTr("Sensor Server")

    Server{
        id: server
        serverStatus: false

        //-- qreal x, qreal y, qreal z --//
//        onGyroscopeData: {
//            lbl_x.text = "x: " + x
//            lbl_y.text = "y: " + y
//            lbl_z.text = "z: " + z
//        }
    }


    ColumnLayout{
        anchors.fill: parent

        //-- tools --//
        Item{
            Layout.fillWidth: true
            Layout.preferredHeight: btn_startSewrver.implicitHeight * 1.5

            RowLayout{
                anchors.fill: parent
                anchors.leftMargin: 170

                Button{
                    id: btn_startSewrver
                    text: "start server"
                    background: Rectangle {
                                implicitWidth: 100
                                implicitHeight: 40
                                color: "#FFA500"
                                border.color: "#000000"
                                border.width: 1
                                radius: 4
                    }
                    onClicked: {

                        if(!server.serverStatus){
                            server.startServer()
                            btn_startSewrver.text = 'close server'
                        }
                        else {
                            server.closeServer()
                            btn_startSewrver.text = 'start server'
                        }

                    }
                }
                Rectangle{
                    Layout.preferredHeight: btn_startSewrver.height * 0.5
                    Layout.preferredWidth: height
                    radius: width * 0.5
                    border.color: "black"
                    border.width: 1
                    smooth: true
                    color:  server.serverStatus ? "Green" : "Red"
                }
                Label{
                    id: lbl_serverStatus
                    text: server.getIpAddress()
                }


                Item{
                    Layout.fillWidth: true
                }

            }


        }


                //-- data --//
//                ColumnLayout{
////                    anchors.fill: parent
//                    anchors.centerIn: parent
//                    spacing: 4

//                    Label{
//                        id: lbl_x
//                        font.pixelSize: 20
//                    }

//                    Label{
//                        id: lbl_y
//                        font.pixelSize: 20
//                    }

//                    Label{
//                        id: lbl_z
//                        font.pixelSize: 20
//                    }
//                }

//            }

        }
    }


