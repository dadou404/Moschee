#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H
#include<QString>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include"initlializationsettingfile.h"
#include"hijri.h"

class DatabaseConnection
{
public:
    DatabaseConnection();

      bool connectDatabase();
      QSqlDatabase db =  QSqlDatabase::addDatabase("QMYSQL");
    bool conencted =true;
    QSqlQuery SelectCountries();
    QSqlQuery SelectCities(QString country1);
    QSqlQuery ShowGPSInformation(QString City1);
    QSqlQuery SelectIslamicEvent();
    QSqlQuery DiyanetData(QString Date);
    QSqlQuery database_method(QString Date);
    bool insert_database_method(QString date,QString fajer,QString fajer_i, QString sharouq, QString dhuhr, QString dhuhr_i, QString asr, QString asr_i,
                                QString magrib, QString magrib_i, QString isha, QString isha_i, QString friday_1, QString friday_2);
    QSqlQuery Quran(int Cate1, int Cate2 , int Aya_Number);
    QSqlQuery Hadith(int Cate1, int Cate2 , int Hadith_Number);

    QString HijriDate();
     hijri HD1ate;
     initlializationSettingFile Settings;

};

#endif // DATABASECONNECTION_H
