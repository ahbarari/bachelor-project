#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "clientsocket.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

//    ClientSocket mSocket;
//    mSocket.test();

    //-- QSetting configuration --//
    app.setOrganizationName("univesity of tehran");
    app.setOrganizationDomain("ut.ac.ir");
    app.setApplicationName("Activity detection");

    //-- socket class --//
    qmlRegisterType<ClientSocket>("com.socket", 1, 0, "ClientSocket");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
