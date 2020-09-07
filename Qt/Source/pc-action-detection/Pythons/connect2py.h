#ifndef CONNECT2PY_H
#define CONNECT2PY_H

#include <QObject>
#include <QDebug>
#include <QProcess>


class Connect2Py : public QObject
{
    Q_OBJECT
public:
    Connect2Py(QObject *parent = nullptr);
    ~Connect2Py();

public slots:
    void readFromPython();
    void setActionFileUrl(QString address);
    void setPythonMainScript(QString script);

private slots:
    void printProcessStatus();
    void printProcessError();
    void printProcessOutput();

private:
    QProcess *process;
    QString fileUrl;
    QString pythonScript;

    const char *string2char(QString str);

signals:
    void detectAction(QString action);
};

#endif // CONNECT2PY_H
