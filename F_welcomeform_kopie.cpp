#include "welcomeform.h"
#include "ui_welcomeform.h"
#include<QInputDialog>
#include<QMessageBox>
#include"region.h"
#include<QtNetwork/QHostInfo>
#include <QNetworkInterface>
#include<QTranslator>
#include<QApplication>
#include<QStringList>
#include<QStringListModel>
#include<QAbstractItemModel>
#include<QListWidget>
#include<QSettings>
#include"initlializationsettingfile.h"
#include<iostream>
WelcomeForm::WelcomeForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeForm)
{
    ui->setupUi(this);
    ui->OnlineConnectionInfo->hide();
    ui->OnlineHint->hide();
    ui->OnlineHint_2->hide();
    ui->line_2->hide();
    ui->Password_Field->setEchoMode(QLineEdit::Password);
    WelcomeForm::setWindowTitle(tr("Setup My Mosque "));
    WelcomeForm::setFixedSize(500,650);
    //---------------------------------------------------------


//------------------------------------------------------------------
}

WelcomeForm::~WelcomeForm()
{
    delete ui;
}

void WelcomeForm::on_NextStepPushButton_clicked()
{
    QString Connectivity="";


    if(ui->Mouse->isChecked()==false && ui->Android_app->isChecked()==false && ui->VNC_Remote->isChecked()==false){
        QMessageBox::information(this,"Error","Please Choose connectivity way",0);
    }else{
        
        initlializationSettingFile StoreSettings;
        if(ui->Mouse->isChecked()==true){
            Connectivity="Mouse";
        }
        if(ui->Android_app->isChecked()==true){
            Connectivity="Andriod_app";
        }
        if(ui->VNC_Remote->isChecked()==true){
            Connectivity="VNC_Remote";
        }
        StoreSettings.StoreSettings("GeneralInformation","connectivity",Connectivity);
        this->close();
        Region Region;
        Region.setWindowFlags(Qt::FramelessWindowHint);
        Region.show();
        Region.exec();


    }

}


void WelcomeForm::on_Mouse_clicked()
{
    ui->OnlineConnectionInfo->hide();
    ui->OnlineHint->hide();
    ui->OnlineHint_2->hide();
    ui->line_2->hide();

}

void WelcomeForm::on_Android_app_clicked()
{
    ui->OnlineConnectionInfo->show();
    ui->OnlineHint->show();
    ui->OnlineHint_2->show();
    ui->line_2->show();


}
void WelcomeForm::on_VNC_Remote_clicked()
{
    ui->OnlineConnectionInfo->show();
    ui->OnlineHint->show();
    ui->OnlineHint_2->show();
    ui->line_2->show();


}
void WelcomeForm::on_on_screen_keyboard_clicked(){

    system("matchbox-keyboard &");


}
void WelcomeForm::on_Add_Network_Button_clicked(){
    std::string double_qutation="\"";
    std::string net="sudo echo \'network={\n         ssid="+double_qutation+""+ui->Network_name->text().toStdString()+"\" \n          psk=\""+ui->Password_Field->text().toStdString()+"\" \n key_mgmt=WPA-PSK \n }\' >> /etc/wpa_supplicant/wpa_supplicant.conf";
    std::cout<<"Text= "<<net<<std::endl;
    system(net.c_str());


}
void WelcomeForm::on_Erease_all_Button_clicked(){

    system("sudo rm /etc/wpa_supplicant/wpa_supplicant.conf");
    system("sudo touch /etc/wpa_supplicant/wpa_supplicant.conf");
    system ("sudo echo 'ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev \n' >>/etc/wpa_supplicant/wpa_supplicant.conf");
    system ("sudo echo 'update_config=1 \n' >>/etc/wpa_supplicant/wpa_supplicant.conf");
    system ("sudo echo 'country=GB \n' >>/etc/wpa_supplicant/wpa_supplicant.conf");
    update_internet_inrerfaces();

}
void WelcomeForm::on_Connect_Button_clicked(){

    system("wpa_cli -i wlan0 reconfigure");
    update_internet_inrerfaces();
}
void WelcomeForm::on_checkBox_stateChanged(int arg1){
    if(arg1==Qt::Checked){

        ui->Password_Field->setEchoMode(QLineEdit::Normal);

    }else {
        ui->Password_Field->setEchoMode(QLineEdit::Password);
    }



}

void WelcomeForm::update_internet_inrerfaces(){
    QStringList list;
    ui->OnlineConnectionInfo->clear();
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for(int i=0; i<interfaces.count(); i++)
    {
    QList<QNetworkAddressEntry> entries = interfaces.at(i).addressEntries();
    for(int j=0; j<entries.count(); j++)
    {
    if(entries.at(j).ip().protocol() == QAbstractSocket::IPv4Protocol)
    {
    qDebug() << entries.at(j).ip().toString();
    qDebug() << entries.at(j).netmask().toString();
    list<<entries.at(j).ip().toString();
    ui->OnlineConnectionInfo->addItem(entries.at(j).ip().toString());
              }
         }
    }


}
