#include <QStandardPaths>
#include <QDir>
#include "connect2py.h"

Connect2Py::Connect2Py(QObject *parent)
{
    pythonScript = "C:/Users/Amirhossein/PycharmProjects/bachelor-project/venv/Scripts/python.exe C:/Users/Amirhossein/PycharmProjects/bachelor-project/main.py";
}

Connect2Py::~Connect2Py()
{

    process->closeWriteChannel();
    process->close();
    process->deleteLater();
}

void Connect2Py::readFromPython()
{

    qDebug() << "start";
    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::SeparateChannels);
    process->start(pythonScript);

    connect(process, SIGNAL(stateChanged(QProcess::ProcessState)), SLOT(printProcessStatus()));
    connect(process, SIGNAL(error(QProcess::ProcessError)), SLOT(printProcessError()));
    connect(process, SIGNAL(readyRead()), SLOT(printProcessOutput()));

}

void Connect2Py::printProcessStatus()
{
    qDebug() << process->state();

}

void Connect2Py::printProcessError()
{
    qDebug() << process->errorString();
}

void Connect2Py::printProcessOutput()
{
    QString str = process->readAll();

    qDebug() << "str:" << str;

    if(str.indexOf("#f-->") > -1){
//        qDebug() << "send file addres " <<  string2char(fileUrl + "\n");
        process->write(string2char(fileUrl + "\n"));
    }
    else if(str.indexOf("up") > -1){
        emit detectAction("UP");
    }
    else if(str.indexOf("down") > -1){
        emit detectAction("DOWN");
    }
    else if(str.indexOf("right") > -1){
        emit detectAction("RIGHT");
    }
    else if(str.indexOf("left") > -1){
        emit detectAction("LEFT");
    }

}

void Connect2Py::setActionFileUrl(QString address)
{
    fileUrl = address;
}

void Connect2Py::setPythonMainScript(QString script)
{
    pythonScript = script;
}

/**
 * @brief Connect2Py::string2char
 *  convert QString to const char*
 * @param str
 * @return
 */
const char *Connect2Py::string2char(QString str)
{

    QByteArray ba = str.toLocal8Bit();
    const char *c_str2 = ba.data();
    return c_str2;
}

