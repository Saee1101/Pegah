#include "debuggerclass.h"
#include <QDir>
#include <QDateTime>
#include <QObject>
QFile* debuggerclass::logfile= Q_NULLPTR;
bool debuggerclass::isInit =false;
QHash<QtMsgType,QString> debuggerclass::contexname={
    {QtMsgType::QtDebugMsg, "Debug"},
    {QtMsgType::QtInfoMsg, "Info"},
    {QtMsgType::QtWarningMsg, "warning"},
    {QtMsgType::QtCriticalMsg, "Critical"},
    {QtMsgType::QtFatalMsg ,"Fatal"}
};
debuggerclass::debuggerclass() {

}

void debuggerclass::init()
{
    if (isInit){
        return;
    }
    logfile = new QFile;
    logfile->setFileName("Tivanex.log");
    logfile->open(QIODevice::Append | QIODevice::Text);
    qInstallMessageHandler(messageoutput);
    logfile->resize(0);
    isInit = true;
}

void debuggerclass::clean()
{
    if(logfile!=Q_NULLPTR){
        logfile->close();
        delete logfile;
    }
}

void debuggerclass::messageoutput(QtMsgType type, const QMessageLogContext &contex, const QString &msg)
{
    QString log = QObject::tr("%1 |%2  |%3   |%4   |%5   |%6 \n").
                  arg(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss")).
                  arg(contexname.value(type)).
                  arg(contex.line).
                  arg(QString(contex.file).section('\\',-1)).
                  arg(QString(contex.function).section('(',-2,-2).section(' ',-1).section(':',-1)).
                  arg(msg);
    logfile->write(log.toLocal8Bit());
    logfile->flush();

}
