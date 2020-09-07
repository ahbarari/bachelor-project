#include "mythread.h"
#include <QTextCodec>
#include <QDateTime>

MyThread::MyThread(int ID, QObject *parent)
    : QThread(parent)
{
    this->socketDescriptor = ID;


//    QTextStream out(&file);
//    out << "The magic number is: " << 49 << "\n";
}

void MyThread::run()
{
    // theared start here

    qDebug() << socketDescriptor << " Starting Thread ..." ;
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDescriptor)){

        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

    qDebug() << socketDescriptor << " client connected" ;

//    QFile file("out.txt");
    /*QDateTime d;
    QString name = d.currentDateTime().toString("yyyy_mm_dd-hh_mm_ss_zzz");
     qDebug() << "name : " << name;
    file.setFileName(name + ".txt");
//    file.setFileName("out.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "can not open file";
        return;
    }
//    QTextStream out(&file);
    out.setDevice(&file);*/

    exec();
}

void MyThread::readyRead()
{
    QByteArray Data = socket->readAll();

//    qDebug() << socketDescriptor << " data in: " << Data ;
//    QString str = "#182_0.699999988079071_36.71500015258789_13.160000801086426#183_-1.2950000762939453_30.764999389648438_12.145000457763672#184_-1.75_24.080001831054688_10.079999923706055#185_-1.3300000429153442_17.780000686645508_7.070000171661377#186_-0.21000000834465027_12.25_3.3949999809265137";

    QString DataAsString = QTextCodec::codecForMib(106 )->toUnicode(Data);

    QStringList list = DataAsString.split("#");

    for(int i=0; i< list.length(); i++){
        if(list.at(i).length() > 0){

            emit reciveData(socketDescriptor, list.at(i));

//            out << list.at(i) << "\n";
            buffer.append(list.at(i));
//            qDebug() << "wrote: " << list.at(i);
        }
    }


//    socket->write(Data);
}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " disconnected" ;

    QDateTime d;
    QString name = d.currentDateTime().toString("yyyy_mm_dd-hh_mm_ss_zzz");
    qDebug() << "name : " << name;
//    file.setFileName(name + ".txt");
    QFile file(name + ".csv");
    //    file.setFileName("out.txt");
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
//        qDebug() << "++wrote: " << buffer.at(i);
    }

    qDebug() << "file closd, size" << file.size() ;
    file.close();
    socket->deleteLater();
    buffer.clear();


    exit(0);
}
