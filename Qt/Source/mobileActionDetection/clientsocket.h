#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>

class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = nullptr);

signals:
    void msg(QString msg);

public slots:
    void connected();
    void dissconnected();
    void byteWritten(qint16 bytes);
    void readyRead();

    bool connectToIp(QString IP);
    void disConnect();
    void sendData(QString Data);

private:
    QTcpSocket *socket;
    bool isSocketConnected = false;
};

#endif // CLIENTSOCKET_H
