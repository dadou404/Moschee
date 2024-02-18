#include "timesetting.h"
#include "ui_timesetting.h"
#include<QDate>
#include<QTime>
#include<QDebug>
#include"activationsettings.h"
#include"initlializationsettingfile.h"
#include <iostream>
TimeSetting::TimeSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeSetting)
{
    ui->setupUi(this);
    const QDate CurrentDate= QDate::currentDate();
    const QTime CurrentTime=QTime::currentTime();
    qDebug()<<CurrentDate<<CurrentTime;
    ui->dateEdit->setDate(CurrentDate);
    ui->timeEdit->setTime(CurrentTime);
}

TimeSetting::~TimeSetting()
{
    delete ui;

}

void TimeSetting::on_NextPush_clicked()
{   initlializationSettingFile StoreSettings;
    StoreSettings.StoreSettings("LocalSetting","Time",ui->timeEdit->text());
    StoreSettings.StoreSettings("LocalSetting","Date",ui->dateEdit->text());
    this->close();

    ActivationSettings activationForm;
    activationForm.setWindowFlags(Qt::FramelessWindowHint);
    activationForm.show();
    activationForm.exec();
}
