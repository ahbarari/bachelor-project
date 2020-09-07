#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include "mythread.h"

class Server : public QTcpServer
{
    Q_OBJECT
    Q_PROPERTY(bool serverStatus READ isServerStatus WRITE setServerStatus NOTIFY serverStatusChanged)

public:
    explicit Server(QObject *parent = nullptr);

    bool isServerStatus();
    void setServerStatus(bool serverStatus);

signals:
    void serverStatusChanged();
    void gyroscopeData(qreal x, qreal y, qreal z);
    void captureAction(QString fileUrl);

public slots:
    void startServer();
    void stopServer();
    void reciveHandler(int socketDescriptor, QString data);
    QString getServerIp();
    void handleCaptureAction(QString fileUrl);

private:
    QTcpServer *server;
    bool serverStatus;

protected:
    void incomingConnection(qintptr socketDescriptor) override;

};

#endif // SERVER_H
