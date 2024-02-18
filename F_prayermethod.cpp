#include "prayermethod.h"
#include"mainwindow.h"
#include "ui_prayermethod.h"
#include<QMessageBox>
#include<QApplication>
#include"mosqueinfo.h"
#include<QTranslator>
#include"region.h"
PrayerMethod::PrayerMethod(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrayerMethod)
{

    ui->setupUi(this);
    QTranslator trans;

    bool interface_lang=StoreSettings.ReadSettings("InterfaceLanguage","Arabic").toBool();
    if(interface_lang){
        trans.load(":/Languages/Arablang.qm");
        qApp->installTranslator(&trans);
        ui->retranslateUi(this);

    }else{
        trans.load(":/Languages/Englang.qm");
        qApp->installTranslator(&trans);
        ui->retranslateUi(this);

    }
}

PrayerMethod::~PrayerMethod()
{
    delete ui;
}

void PrayerMethod::on_Next_clicked()
{


    QString Prayer_Method=ui->MethodComboBox->currentText();
    if(ui->MethodComboBox->currentText()=="ديانات")
        Prayer_Method="Diyanet";
    if(ui->MethodComboBox->currentText()=="الاتحاد العالمي الاسلامي")
      Prayer_Method="Muslim World League (MWL)";
    if(ui->MethodComboBox->currentText()=="المجمع الالسلامي شمال امريكيا")
    Prayer_Method="Islamic Society of North America (ISNA)";
    if(ui->MethodComboBox->currentText()=="مصر")
    Prayer_Method="Egyptian General Authority of Survey";
    if(ui->MethodComboBox->currentText()=="ام القرى")
     Prayer_Method="Umm al-Qura University";
    if(ui->MethodComboBox->currentText()=="جامعة العلوم الاسلامية")
    Prayer_Method="University of Islamic Sciences";
    if(ui->MethodComboBox->currentText()=="جعفري")
      Prayer_Method="Jafri";


    StoreSettings.StoreSettings("PrayerSettings","Method",Prayer_Method);
    StoreSettings.StoreSettings("PrayerSettings","AsrMethod",ui->AsrComBox->currentText());
    StoreSettings.StoreSettings("PrayerAdjustment","AddedTimeFajer",0);
    StoreSettings.StoreSettings("PrayerAdjustment","AddedTimeShrouq",0);
    StoreSettings.StoreSettings("PrayerAdjustment","AddedTimeDhuhr",0);
    StoreSettings.StoreSettings("PrayerAdjustment","AddedTimeAsr",0);
    StoreSettings.StoreSettings("PrayerAdjustment","AddedTimeMagrib",0);
    StoreSettings.StoreSettings("PrayerAdjustment","AddedTimeIsha",0);
    StoreSettings.StoreSettings("volume","volume",100);
    this->close();
    MosqueInfo mosqueInfo;
    mosqueInfo.setWindowFlags(Qt::FramelessWindowHint);
    mosqueInfo.show();
    mosqueInfo.exec();


}
void PrayerMethod::on_BackPush_clicked(){

    Region Re;
    this->close();

    Re.setWindowFlags(Qt::FramelessWindowHint);
    Re.show();
    Re.exec();

}

