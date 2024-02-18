#include "wirelesslog.h"
#include "ui_wirelesslog.h"
#include <QNetworkAccessManager>
#include<QNetworkReply>
#include<QMessageBox>
wirelesslog::wirelesslog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wirelesslog)
{
    ui->setupUi(this);

   // QObject::connect(ui->buttonBox,SIGNAL(clicked),this,SLOT(accept()));
   // QObject::connect(ui->buttonBox,SIGNAL(clicked),this,SLOT(reject()));


}

wirelesslog::~wirelesslog()
{
    delete ui;
}
/*
void wirelesslog::on_buttonBox_accepted()
{





}
*/

void wirelesslog::on_keyboard_clicked()
{
    system("matchbox-keyboard &");

}

void wirelesslog::on_keyboard_2_clicked()
{


    QNetworkAccessManager nam;

    QNetworkRequest req(QUrl("http://www.google.com"));
    QNetworkReply* reply=nam.get(req);
    QEventLoop loop;
    QObject::connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();

    if(reply->bytesAvailable())
        QMessageBox::information(this,"info","You are connected");
    else {
        QMessageBox::information(this,"info","You are not connected");
        system("sudo rm /etc/wpa_supplicant/wpa_supplicant.conf");
        system("sudo touch /etc/wpa_supplicant/wpa_supplicant.conf");
        system ("sudo echo 'ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev \n' >>/etc/wpa_supplicant/wpa_supplicant.conf");
        system ("sudo echo 'update_config=1 \n' >>/etc/wpa_supplicant/wpa_supplicant.conf");
        system ("sudo echo 'country=DE \n' >>/etc/wpa_supplicant/wpa_supplicant.conf");
        std::string double_qutation="\"";
        std::string net="sudo echo \'network={\n         ssid="+double_qutation+""+ui->network_name->text().toStdString()+"\" \n          psk=\""+ui->network_password->text().toStdString()+"\" \n key_mgmt=WPA-PSK \n }\' >> /etc/wpa_supplicant/wpa_supplicant.conf";
        system(net.c_str());
        system("ifconfig wlan0 down");
        system("sleep 30");
        system("ifconfig wlan0 up");

    }
}

void wirelesslog::on_keyboard_3_clicked()
{
    this->close();
}
