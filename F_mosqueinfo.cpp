#include "mosqueinfo.h"
#include "ui_mosqueinfo.h"
#include <QSysInfo>
#include<QDebug>
#include<timesetting.h>
#include<QMessageBox>
#include"mainwindow.h"
#include"mosqueinfo.h"
#include"prayermethod.h"
MosqueInfo::MosqueInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MosqueInfo)
{
    ui->setupUi(this);
    qDebug()<<QSysInfo::machineHostName()<<QSysInfo::macVersion()<<QSysInfo::productType()<<QSysInfo::prettyProductName();

    QTranslator trans;

    bool interface_lang=StoreSettings.ReadSettings("InterfaceLanguage","Arabic").toBool();
    if(interface_lang){
        trans.load(":/Languages/Arablang.qm");
        qApp->installTranslator(&trans);
        ui->retranslateUi(this);

        qDebug()<<"Loading the language";
    }else{
        trans.load(":/Languages/Englang.qm");
        qApp->installTranslator(&trans);
        ui->retranslateUi(this);
    }
}

MosqueInfo::~MosqueInfo()
{
    delete ui;
}

void MosqueInfo::on_NextPush_clicked()
{
    if(ui->EmailEdit->text()=="" || ui->MosqueNameEdit->text()=="" || ui->OwnerProductEdit->text()=="" || ui->PhoneNumberEdit->text()==""){

        QMessageBox::warning(this,"forget some requirement", "there is some fields not filled . they are require",0,0);

    }else{
    StoreSettings.StoreSettings("MosqueInformation","Name",ui->MosqueNameEdit->text());
    StoreSettings.StoreSettings("MosqueInformation","Owner",ui->OwnerProductEdit->text());
    StoreSettings.StoreSettings("MosqueInformation","PhoneNumber",ui->PhoneNumberEdit->text());
    StoreSettings.StoreSettings("MosqueInformation","Email",ui->EmailEdit->text());
    StoreSettings.StoreSettings("MosqueInformation","Street",ui->Street->text());
    StoreSettings.StoreSettings("MosqueInformation","house_no",ui->house_no->text());
    StoreSettings.StoreSettings("MosqueInformation","zip",ui->zip->text());



    this->close();
    if(QMessageBox::information(this,"Finish","Setting is performed successfully",QMessageBox::Ok)==QMessageBox::Ok){
        this->close();
        MainWindow *w= new MainWindow;
        w->showFullScreen();
        w->show();
    }
    }
}



void MosqueInfo::on_pushButton_clicked(){

    system("matchbox-keyboard &");


}
void MosqueInfo::on_BackPush_clicked(){
    this->close();

    PrayerMethod mosqueInfo;
    mosqueInfo.setWindowFlags(Qt::FramelessWindowHint);
    mosqueInfo.show();
    mosqueInfo.exec();
}
