#include "clientsocket.h"

ClientSocket::ClientSocket(QObject *parent) : QObject(parent)
{

}


void ClientSocket::connected()
{
    qDebug() << "connected";
    emit msg("connected");
}

void ClientSocket::dissconnected()
{
    qDebug() << "dissconnected";
    emit msg("dissconnected");
}

void ClientSocket::byteWritten(qint16 bytes)
{

    qDebug() << "we wrote " << bytes;
}

void ClientSocket::readyRead()
{

    qDebug() << "reading... ";
    QString str = socket->readAll();
    qDebug() << str;
}

bool ClientSocket::connectToIp(QString IP)
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(dissconnected()), this, SLOT(dissconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(byteWritten(qint16)), this, SLOT(byteWritten(qint16)));

    qDebug() << "connecting...";
    emit msg("connecting to " + IP + "...");

    socket->connectToHost(IP, 1234);

    if(!socket->waitForConnected(1000)){

        qDebug() << "Error:" << socket->errorString();
        emit msg("Error:" + socket->errorString());
        isSocketConnected = false;
        return false;
    }

    isSocketConnected = true;
    return true;
}

void ClientSocket::disConnect()
{
    socket->deleteLater();
    emit msg("disConnect");
}

void ClientSocket::sendData(QString Data)
{
    if(isSocketConnected){

        socket->write(Data.toUtf8());
    }
}
