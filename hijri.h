#ifndef HIJRI_H
#define HIJRI_H

#include<QString>
#include<QSettings>
#include<QApplication>

class hijri
{
public:
    QString Dir_setting_file=QApplication::applicationDirPath()+"/Settings.ini";
    QSettings* Settings_Pro = new QSettings(Dir_setting_file, QSettings::IniFormat);
    int adjustDay = Settings_Pro->value("Hijri/AddingDay",0).toInt();
    hijri();
   QString PrintCalender(int d, int m, int y,int adjustDay);
   int IslamicDate(int month, int day, int year);
   int LastDayOfIslamicMonth(int month, int year);
   bool IsIslamicLeapYear(int year);
   int calcAbsGregorianDays(int d, int m, int y);
   int LastDayOfGregorianMonth(int month, int year);
   QString PrintCalend();
   char const *getMonthName(int m);
   QString reutunDate(int d, int m, int y,int adjustDay);


};

#endif // HIJRI_H
