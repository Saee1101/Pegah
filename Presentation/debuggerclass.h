#ifndef DEBUGGERCLASS_H
#define DEBUGGERCLASS_H
#include <QDebug>
#include <QFile>
#include <QHash>
class debuggerclass
{
public:
    debuggerclass();
    static void init();
    static void clean();
    static void messageoutput(QtMsgType type,const QMessageLogContext & contex,const QString& msg);
    static QFile* logfile;
    static  bool isInit;
    static  QHash<QtMsgType,QString> contexname;
};

#endif // DEBUGGERCLASS_H
