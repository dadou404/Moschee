#include "region.h"
#include "ui_region.h"
#include<QFile>
#include"databaseconnection.h"
#include<QStringList>
#include<QDebug>
#include"mosqueinfo.h"
#include "prayermethod.h"

Region::Region(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Region)
{
    ui->setupUi(this);
    Region::setWindowTitle("Region Settings");
    instant.connectDatabase();
    QSqlQuery Query;
    Query=instant.SelectCountries();
    QString LastEntry="";
    while(Query.next()){
if(Query.value(0).toString()!=LastEntry){
    ui->CountryListBox->addItem(Query.value(0).toString());
  }
LastEntry = Query.value(0).toString();




    }

    const QDate CurrentDate= QDate::currentDate();
    const QTime CurrentTime=QTime::currentTime();
    qDebug()<<CurrentDate<<CurrentTime;

    ui->dateEdit->setDate(CurrentDate);
    ui->timeEdit->setTime(CurrentTime);
}

Region::~Region()
{
    delete ui;

}

void Region::on_CountryListBox_currentTextChanged(const QString &arg1)
{
    QSqlQuery Query;
    const QString ComboText=ui->CountryListBox->currentText();
        ui->CityListBox->clear();
        Query=instant.SelectCities(ComboText);
    while(Query.next()){
        qDebug()<<Query.value(0).toString();
           ui->CityListBox->addItem(Query.value(0).toString());
    }
}



void Region::on_CityListBox_currentTextChanged(const QString &arg1)
{

    QSqlQuery Query;
    const QString ComboText=ui->CityListBox->currentText();
   // qDebug()<<ComboText;
    Query=instant.ShowGPSInformation(ComboText);
    Query.first();
    ui->LongitudTextbox->setText(Query.value(0).toString());
    ui->LatitudeTextbox->setText(Query.value(1).toString());
    ui->LongitudTextbox->setEnabled(false);
    ui->LatitudeTextbox->setEnabled(false);
    //qDebug()<<Query.value(0).toString()<<Query.value(1).toString();
}

void Region::on_ChangingLanLonPush_clicked()
{
    ui->LongitudTextbox->setEnabled(true);
    ui->LatitudeTextbox->setEnabled(true);
    system("matchbox-keyboard &");
}


void Region::on_BackPush_clicked(){

    this->close();
    WelcomeForm Welcom;
    Welcom.show();
    Welcom.setWindowFlags(Qt::FramelessWindowHint);
    Welcom.exec();
    this->close();
}


void Region::on_NextPush_clicked()
{

    Settings.StoreSettings("GPS_Information","City",ui->CityListBox->currentText());
    Settings.StoreSettings("GPS_Information","Country",ui->CountryListBox->currentText());
    Settings.StoreSettings("GPS_Information","Langitud",ui->LongitudTextbox->text());
    Settings.StoreSettings("GPS_Information","Latitude",ui->LatitudeTextbox->text());
    Settings.StoreSettings("LocalSettings","TimeZone",ui->TimeZoneEdit->text());
    Settings.StoreSettings("GeneralInformation","SetupLanguage",setLang);
    Settings.StoreSettings("Position","Clock_x",20);
    Settings.StoreSettings("Position","Clock_y",20);
    Settings.StoreSettings("Position","Prayer_X_W_Position",1600);
    Settings.StoreSettings("Position","Prayer_Y_W_Position",20);
    std::string sdate = "sudo date -s '"+ui->dateEdit->text().toStdString();
    std::string stime= " "+ui->timeEdit->text().toStdString()+"'";
    std::string sdatetime = sdate+stime;
        char cstr[sdatetime.size() + 1];
        strcpy(cstr, sdatetime.c_str());

    char full_command[300];

    std::sprintf(full_command,"%s",cstr);
    qDebug()<<full_command;
    system(full_command);

    this->close();
    PrayerMethod PrayerForm;
    PrayerForm.setWindowFlags(Qt::FramelessWindowHint);
    PrayerForm.show();
    PrayerForm.exec();

}
void Region::on_Language_List_currentIndexChanged(int index){

    QTranslator trans;



    if(index==0){
        trans.load(":/Languages/Englang.qm");
        Settings.StoreSettings("InterfaceLanguage","Arabic",false);
        setLang="English";
        Lang_Index=0;
      qApp->installTranslator(&trans);
      qDebug()<<"Hellp ot orin Deustch";
      ui->retranslateUi(this);

    }
     if(index==1){
      if (trans.load(":/Languages/Arablang.qm"))

         {
             qDebug()<<"Hellp ot orin arabic";
             Settings.StoreSettings("InterfaceLanguage","Arabic",true);


         }else {
             qDebug()<<"Hell";

         }
            setLang="Arabic";
            Lang_Index=1;
            qApp->installTranslator(&trans);
            ui->retranslateUi(this);



    }

}
