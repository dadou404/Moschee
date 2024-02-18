#include "activationsettings.h"
#include "ui_activationsettings.h"
#include"prayermethod.h"
#include"initlializationsettingfile.h"
#include"mosqueinfo.h"
ActivationSettings::ActivationSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActivationSettings)
{
    ui->setupUi(this);
    ui->Serial->setDisabled(true);
    ui->Serial_2->setDisabled(true);
    ui->Serial_3->setDisabled(true);
    ui->Serial_4->setDisabled(true);
}

ActivationSettings::~ActivationSettings()
{
    delete ui;

}

void ActivationSettings::on_Offline_Activation_clicked()
{
    ui->Serial->setDisabled(false);
    ui->Serial_2->setDisabled(false);
    ui->Serial_3->setDisabled(false);
    ui->Serial_4->setDisabled(false);

}

void ActivationSettings::on_NextButton_clicked()
{
    initlializationSettingFile StoreSettings;
    QString  Serial=ui->Serial->text()+"-"+ui->Serial_2->text()+"-"+ui->Serial_3->text()+"-"+ui->Serial_4->text();
    StoreSettings.StoreSettings("Acitivation","Method",Serial);
    this->close();
    MosqueInfo mosqueInfo;
    mosqueInfo.setWindowFlags(Qt::FramelessWindowHint);
    mosqueInfo.show();
    mosqueInfo.exec();
}
