
#include "hijri.h"
#include <QString>
#include<QVariant>
#include<QSettings>

hijri::hijri()
{

}
QString hijri::PrintCalend() {
    const time_t current_time = time(NULL);
    tm * t = localtime(&current_time);
     int d = t -> tm_mday, m = (t -> tm_mon) + 1, y = (t -> tm_year) + 1900;

    QString Dateah=PrintCalender(d, m , y, adjustDay);
    return Dateah;
       }

int hijri::LastDayOfGregorianMonth(int month, int year) {
// Compute the last date of the month for the Gregorian calendar.

  switch (month) {
  case 2:
    if ((((year % 4) == 0) && ((year % 100) != 0))
        || ((year % 400) == 0))
      return 29;
    else
      return 28;
  case 4:
  case 6:
  case 9:
  case 11: return 30;
  default: return 31;
  }
}

int hijri::calcAbsGregorianDays(int d, int m, int y) {
    int N = d;
    for (int i = m - 1; i > 0; i--)
        N += LastDayOfGregorianMonth(i, y);

    return N + (y - 1) * 365
             + (y - 1) / 4
             - (y - 1) / 100
             + (y - 1) / 400;
}

bool hijri::IsIslamicLeapYear(int year) {
// True if year is an Islamic leap year

  if ((((11 * year) + 14) % 30) < 11)
    return true;
  else
    return false;
}

int hijri::LastDayOfIslamicMonth(int month, int year) {
// Last day in month during year on the Islamic calendar.

  if (((month % 2) == 1) || ((month == 12) && IsIslamicLeapYear(year)))
    return 30;
  else
    return 29;
}

const int IslamicEpoch = 227014; // Absolute date of start of Islamic calendar

int hijri::IslamicDate(int month, int day, int year) {
    return (day                      // days so far this month
            + 29 * (month - 1)       // days so far...
            + month/2                //            ...this year
            + 354 * (year - 1)       // non-leap days in prior years
            + (3 + (11 * year)) / 30 // leap days in prior years
            + IslamicEpoch);                // days before start of calendar
}

char const* hijri::getMonthName(int m)
{
    switch (m)
    {
        case 1:
            return "محرّم";
        case 2:
            return "صفر";
        case 3:
            return "ربيع الأول";
        case 4:
            return " ربيع الاخر";
        case 5:
            return "جمادى الأولى";
        case 6:
            return "جمادى الآخرة";
        case 7:
            return "رجب";
        case 8:
            return "شعبان";
        case 9:
            return "رمضان";
        case 10:
            return "شوال";
        case 11:
            return "ذو العقدة";
        case 12:
            return "ذو الحجة";
    }
    return "";
}
QString hijri::PrintCalender(int d, int m, int y,int adjustDay){
    d = calcAbsGregorianDays(d, m, y);
    int month, day, year;

    // Search forward year by year from approximate year
    year = (d - IslamicEpoch) / 355;

    while (d >= IslamicDate(1, 1, year))
        year++;

    year--;
    // Search forward month by month from Muharram
    month = 1;
    while (d > IslamicDate(month, LastDayOfIslamicMonth(month, year), year))
        month++;

    day = d - IslamicDate(month, 1, year)+ adjustDay;// adding days for hijri month by + and -

    QString Hijri =QVariant(day).toString()+"-"+ getMonthName(month) +"-"+QVariant(year).toString() ;
//cout<<year<<"-"<<getMonthName(month)<<"-"<<day;

return Hijri;
}

QString hijri::reutunDate(int d, int m, int y, int adjustDay){

    QString Date[3];

    d = calcAbsGregorianDays(d, m, y);
    int month, day, year;

    // Search forward year by year from approximate year
    year = (d - IslamicEpoch) / 355;

    while (d >= IslamicDate(1, 1, year))
        year++;

    year--;
    // Search forward month by month from Muharram
    month = 1;
    while (d > IslamicDate(month, LastDayOfIslamicMonth(month, year), year))
        month++;

    day = d - IslamicDate(month, 1, year)+ adjustDay;// adding days for hijri month by + and -

    QString Hijri =QVariant(day).toString()+"-"+ getMonthName(month) +"-"+QVariant(year).toString() ;
//cout<<year<<"-"<<getMonthName(month)<<"-"<<day;
    Date[0]=day;
    Date[1]=month;
    Date[2]=year;



    return Hijri;
}
