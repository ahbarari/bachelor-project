#include "server.h"
#include <QNetworkInterface>
#include <string>

Server::Server(QObject *parent) : QTcpServer(parent)
{
    serverStatus = false;

    /*server = new QTcpServer(this);


    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any,1234)){
        qDebug() << "server could not start";
    }
    else{
        qDebug() << "server started";
    }*/
}
void Server::newConnection()
{
    /*qDebug() << "client connected";

    QTcpSocket *socket = server->nextPendingConnection();

    socket->write("hello client\r\n");
    socket->flush();

    socket->waitForBytesWritten(3000);

    socket->close();*/
}

void Server::reciveHandler(int socketDescriptor, QString data)
{
//    qDebug() << socketDescriptor << ": " << data;

    QStringList list = data.split("_");
    if(list.length() != 4) return;

//    qDebug() << socketDescriptor << ": " << list.at(1).toFloat();

    emit gyroscopeData(list.at(1).toFloat(), list.at(2).toFloat(), list.at(3).toFloat());

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

void Server::closeServer()
{
    if(this->serverStatus==true){
        qDebug() << "closing server";
        serverStatus = false;
        emit serverStatusChanged();
        this->close();
    }
}

bool Server::isServerStatus()
{
    return this->serverStatus;
}

QString Server::getIpAddress()
{
    qDebug() << "get ip...";
    QString ip_address = "";
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
        {
             ip_address = address.toString();
             qDebug() << "ip: " << ip_address;
        }
    }
    return ip_address;
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
    thread->start();

}
