#include "mythread.h"
#include <QTextCodec>
#include <QDateTime>
#include <QDir>

MyThread::MyThread(int ID, QObject *parent)
    : QThread(parent)
{
    this->socketDescriptor = ID;

}

void MyThread::run()
{
    // thread start here

    qDebug() << socketDescriptor << " Starting Thread ..." ;
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDescriptor)){

        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

    qDebug() << socketDescriptor << " client connected" ;



    exec();
}

void MyThread::readyRead()
{
    QByteArray Data = socket->readAll();

    QString DataAsString = QTextCodec::codecForMib(106 )->toUnicode(Data);

    QStringList list = DataAsString.split("#");

    for(int i=0; i< list.length(); i++){
        if(list.at(i).length() > 0){

            emit reciveData(socketDescriptor, list.at(i));

            buffer.append(list.at(i));
        }
    }


}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " disconnected" ;

    QDateTime d;
    QString name = QString::number(d.currentMSecsSinceEpoch());
    qDebug() << "name : " << name;
    QFile file(name + ".csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "can not open file";
        return;
    }



    QTextStream out1(&file);
    out1.setDevice(&file);

     out1 << "ACC_or_GYR,milisecond,x,y,z" << "\n";

    for(int i=0; i< buffer.length(); i++){

        QStringList t = buffer.at(i).split("_");
        out1 << t.join(',') << "\n";
    }

    qDebug() << "file closd, size" << file.size() ;
    file.close();
    socket->deleteLater();
    buffer.clear();

    qDebug() << "current dir: " << QDir::currentPath();
    QString url = QDir::currentPath() + "/" + name + ".csv";
    emit captureAction(url);

    exit(0);
}
