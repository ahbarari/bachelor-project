#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QFile>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(int ID, QObject *parent = nullptr);
    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);
    void reciveData(int socketDescriptor, QString data);

public slots:
    void readyRead();
    void disconnected();


private:
    QTcpSocket *socket;
    int socketDescriptor;

//    QFile file;
//    QTextStream out;
    QStringList buffer;

};

#endif // MYTHREAD_H
