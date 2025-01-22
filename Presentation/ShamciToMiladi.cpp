#include "ShamciToMiladi.h"

ShamciToMiladi::ShamciToMiladi(QObject *parent)
    : QObject{parent}
{}

ShamciToMiladi::SDATE ShamciToMiladi::MiladiToShamsi(int iMiladiMonth, int iMiladiDay, int iMiladiYear)
{
    int  shamsiDay, shamsiMonth, shamsiYear;
    int  dayCount,farvardinDayDiff,deyDayDiff ;
    int  sumDayMiladiMonth[] = {0,31,59,90,120,151,181,212,243,273,304,334};
    int  sumDayMiladiMonthLeap[]= {0,31,60,91,121,152,182,213,244,274,305,335};
    SDATE  shamsidate;

    farvardinDayDiff=79;

    if (MiladiIsLeap(iMiladiYear))
    {
        dayCount = sumDayMiladiMonthLeap[iMiladiMonth-1] + iMiladiDay;
    }
    else
    {
        dayCount = sumDayMiladiMonth[iMiladiMonth-1] + iMiladiDay;
    }
    if((MiladiIsLeap(iMiladiYear - 1)))
    {
        deyDayDiff = 11;
    }
    else
    {
        deyDayDiff = 10;
    }
    if (dayCount > farvardinDayDiff)
    {
        dayCount = dayCount - farvardinDayDiff;
        if (dayCount <= 186)
        {
            switch (dayCount%31)
            {
            case 0:
                shamsiMonth = dayCount / 31;
                shamsiDay = 31;
                break;
            default:
                shamsiMonth = (dayCount / 31) + 1;
                shamsiDay = (dayCount%31);
                break;
            }
            shamsiYear = iMiladiYear - 621;
        }
        else
        {
            dayCount = dayCount - 186;
            switch (dayCount%30)
            {
            case 0:
                shamsiMonth = (dayCount / 30) + 6;
                shamsiDay = 30;
                break;
            default:
                shamsiMonth = (dayCount / 30) + 7;
                shamsiDay = (dayCount%30);
                break;
            }
            shamsiYear = iMiladiYear - 621;
        }
    }
    else
    {
        dayCount = dayCount + deyDayDiff;

        switch (dayCount%30)
        {
        case 0 :
            shamsiMonth = (dayCount / 30) + 9;
            shamsiDay = 30;
            break;
        default:
            shamsiMonth = (dayCount / 30) + 10;
            shamsiDay = (dayCount%30);
            break;
        }
        shamsiYear = iMiladiYear - 622;

    }
    shamsidate.iYear = shamsiYear;
    shamsidate.iMonth = shamsiMonth;
    shamsidate.iDay = shamsiDay;
    return  shamsidate;
}

int ShamciToMiladi::MiladiIsLeap(int miladiYear)
{
    if(((miladiYear % 100)!= 0 && (miladiYear % 4) == 0) || ((miladiYear % 100)== 0 && (miladiYear % 400) == 0))
        return 1;
    else
        return 0;
}



