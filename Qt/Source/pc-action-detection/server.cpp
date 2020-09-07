#include <QNetworkInterface>
#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    serverStatus = false;

}

void Server::reciveHandler(int socketDescriptor, QString data)
{

    QStringList list = data.split("_");
    if(list.length() != 4) return;


    emit gyroscopeData(list.at(1).toFloat(), list.at(2).toFloat(), list.at(3).toFloat());

}

QString Server::getServerIp()
{
    QStringList ips;
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost){

             qDebug() << address.toString();
             ips.append(address.toString());
        }
    }

    return ips.join("_");
}

void Server::handleCaptureAction(QString fileUrl)
{
    emit captureAction(fileUrl);
}

void Server::startServer()
{
    if(!this->listen(QHostAddress::Any, 1234)){

        qDebug() << "could not start server";
        serverStatus = false;
        emit serverStatusChanged();
    }
    else{

        qDebug() << "Listening...";
        serverStatus = true;
        emit serverStatusChanged();
    }
}

void Server::stopServer()
{

    qDebug() << "stop server";
    this->close();
    serverStatus = false;
    emit serverStatusChanged();
}

bool Server::isServerStatus()
{
    return this->serverStatus;
}

void Server::setServerStatus(bool serverStatus)
{
    this->serverStatus = serverStatus;
}


void Server::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting...";
    MyThread *thread = new MyThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(reciveData(int, QString)), this, SLOT(reciveHandler(int, QString)));
    connect(thread, SIGNAL(captureAction(QString)), this, SLOT(handleCaptureAction(QString)));
    thread->start();

}
