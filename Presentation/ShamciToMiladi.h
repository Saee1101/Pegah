#ifndef SHAMCITOMILADI_H
#define SHAMCITOMILADI_H

#include <QObject>

class ShamciToMiladi : public QObject
{
    Q_OBJECT

public:
    typedef struct _SHAMSIDATE
    {
        int iYear;
        int iMonth;
        int iDay;
    }SDATE;
    explicit ShamciToMiladi(QObject *parent = nullptr);
    SDATE MiladiToShamsi(int iMiladiMonth,int iMiladiDay,int iMiladiYear);
    int MiladiIsLeap(int miladiYear);
signals:
};

#endif // SHAMCITOMILADI_H
