#include "databaseconnection.h"
#include <QMessageBox>
#include<QDebug>
#include"hijri.h"
#include<QDate>
#include<QDebug>
#include<QString>
#include<cstdlib>

DatabaseConnection::DatabaseConnection()
{
  //  connectDatabase();
}

bool DatabaseConnection::connectDatabase(){
    QMessageBox msg;

    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("allahisone");
    db.setDatabaseName("mymosque");

    if(db.open()){
     //  msg.setText("the database connected");
     //   msg.exec();
        return true;
    }
    else{
        msg.setText("the database unconnected");
        msg.exec();
        return false;
    }

}

QSqlQuery DatabaseConnection::SelectCountries(){
    QSqlQuery Citiesquery;


            Citiesquery.prepare("SELECT `country` FROM `worldcities_xlsx_sheet1` WHERE 1");
            Citiesquery.exec();



            // extracts the first row from the onboard database

            return Citiesquery;
}

QSqlQuery DatabaseConnection::SelectCities(QString country1){


    QSqlQuery query;
            query.prepare("SELECT `city_ascii` FROM `worldcities_xlsx_sheet1` WHERE `country`='"+country1+"'");
            query.bindValue("country",country1);
            query.exec();




            // extracts the first row from the onboard database

            return query;
}

QSqlQuery DatabaseConnection::ShowGPSInformation(QString City1){


    QSqlQuery query;

            query.prepare("SELECT `lng`,`lat` FROM `worldcities_xlsx_sheet1` WHERE `city_ascii`='"+City1+"'");
            query.bindValue("city_ascii",City1);
            query.exec();


            // extracts the first row from the onboard database

            qDebug()<<query.size();
            return query;
}

QString DatabaseConnection::HijriDate(){
    QString  HDate;


    int Day = QDate::currentDate().day();
    int Month = QDate::currentDate().month();
    int Year = QDate::currentDate().year();

    int adjust=Settings.ReadSettings("Hijri","AddedDays").toInt();
    HDate= HD1ate.reutunDate(Day+adjust,Month,Year,0);


    return HDate;
}

QSqlQuery DatabaseConnection::SelectIslamicEvent(){
    // connectDatabase();
    QSqlQuery IslamicEventquery(db);

    QStringList Date = HijriDate().split("-");
    QString Day = Date.at(0);
    QString Month = Date.at(1);
        qDebug()<<"Select Islamic Event"<<connectDatabase();
    IslamicEventquery.prepare("SELECT `Event` , `Islamic_Event` , `Category` FROM `Hijri` WHERE `Month`='"+Month+"' and `Day` = '"+Day+"'");
    IslamicEventquery.bindValue("Month",Month);
    IslamicEventquery.bindValue("Day",Day);

    IslamicEventquery.exec();

    return IslamicEventquery;

}
QSqlQuery DatabaseConnection::Quran(int Cat_Number1, int Cat_Number2 , int Aya_Number){

    //connectDatabase();
    QSqlQuery Quranquery;


    qDebug()<<"Quran"<<connectDatabase();

    Quranquery.prepare("SELECT `Arabic_text` , `English_Text` , `Ref_Aya` , `Ref_Sura` FROM `Aya`  WHERE `Cat_Number1` = :Cat_Number1 and `Cat_Number2` = :Cat_Number2 and `Aya_Number` = :Aya_Number");
    Quranquery.bindValue(":Cat_Number1",Cat_Number1);
    Quranquery.bindValue(":Cat_Number2",Cat_Number2);
    Quranquery.bindValue(":Aya_Number",Aya_Number);
    Quranquery.exec();



    return Quranquery;

}

QSqlQuery DatabaseConnection::Hadith(int Cat_Number1, int Cat_Number2 , int Hadith_Number){

    QSqlQuery Hadithquery;
    //connectDatabase();
        qDebug()<<"Hadith"<<connectDatabase();

    Hadithquery.prepare("SELECT `Arabic_text` , `English_Text` , `Narr`  FROM `Hadith` WHERE `Cat_Number1`= :Cat_Number1 and `Cat_Number2` = :Cat_Number2 and `Hadith_Number` = :Hadith_Number");
    Hadithquery.bindValue(":Cat_Number1",Cat_Number1);
    Hadithquery.bindValue(":Cat_Number2",Cat_Number2);
    Hadithquery.bindValue(":Hadith_Number",Hadith_Number);
    Hadithquery.exec();



    return Hadithquery;

}

QSqlQuery DatabaseConnection::DiyanetData(QString Date)
{
    QSqlQuery Diyanet(db);
    connectDatabase();
    Diyanet.prepare("SELECT `fjr` , `shrq` , `dhr` , `asr` , `mgrb` , `ash`  FROM `pry_table` WHERE `Date`= '"+Date+"'");
    Diyanet.bindValue("Date",Date);
    Diyanet.exec();
    return Diyanet;

}
QSqlQuery DatabaseConnection::database_method(QString Date){

    QSqlQuery database(db);
    connectDatabase();
    database.prepare("SELECT `fajer` , `sharouq` , `dhuhr` , `asr` , `magrib` , `isha`  FROM `database_method` WHERE `date`= '"+Date+"'");
    database.bindValue("date",Date);
    database.exec();
    return database;

}
bool DatabaseConnection::insert_database_method(QString date,QString fajer,QString fajer_i, QString sharouq, QString dhuhr, QString dhuhr_i, QString asr, QString asr_i,
                                                QString magrib, QString magrib_i, QString isha, QString isha_i, QString friday_1, QString friday_2 ){
QSqlQuery database(db);

            connectDatabase();

        database.prepare("REPLACE INTO `database_method` (`id`, `date`, `fajer`, `fajer_i`, `sharouq`, `dhuhr`, `dhuhr_i`, `asr`, `asr_i`, `magrib`, `magrib_i`, `isha`, `isha_i`, `friday_1`, `friday_2`) "
                         "VALUES (NULL, :date, :fajer, :fajer_i, :sharouq, :dhuhr, :dhuhr_i, :asr, :asr_i, :magrib, :magrib_i, :isha, :isha_i, :friday_1, :friday_2)");
        database.bindValue(":date",date);
        database.bindValue(":fajer",fajer);
        database.bindValue(":fajer_i",fajer_i);
        database.bindValue(":sharouq",sharouq);
        database.bindValue(":dhuhr",dhuhr);
        database.bindValue(":dhuhr_i",dhuhr_i);
        database.bindValue(":asr",asr);
        database.bindValue(":asr_i",asr_i);
        database.bindValue(":magrib",magrib);
        database.bindValue(":magrib_i",magrib_i);
        database.bindValue(":isha",isha);
        database.bindValue(":isha_i",isha_i);
        database.bindValue(":friday_1",friday_1);
        database.bindValue(":friday_2",friday_2);
        if(database.exec()){
            qDebug()<<database.exec();

     return true;
     }
        else{


            return false;
        }

}
