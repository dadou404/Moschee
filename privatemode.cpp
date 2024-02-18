#include "privatemode.h"
#include "ui_privatemode.h"
#include "privacysetting.h"
#include"mainwindow.h"
#include <QSettings>
#include <QMessageBox>

#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>


PrivateMode::PrivateMode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrivateMode)
{
    ui->setupUi(this);

    QString filePath = "storedmosque.json";
    QFile file(filePath);

    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    file.close();


    if (!jsonDoc.isNull()) {
        QJsonObject jsonObj = jsonDoc.object();
        QJsonArray itemsArray = jsonObj["name"].toArray();

        foreach (const QJsonValue &itemValue, itemsArray) {
            QJsonObject itemObject = itemValue.toObject();
            QString itemName = itemObject["name"].toString();
            ui->comboBox->addItem(itemName);
        }
    }
}
PrivateMode::~PrivateMode()
{
    delete ui;
}

void PrivateMode::on_pushOk_clicked()
{
    QString filePath = "storedmosque.json";
    QFile file(filePath);

    // Open the file in read-only mode
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file:" << file.errorString();
     }

    // Read the JSON data from the file
    QByteArray jsonData = file.readAll();

    // Close the file
    file.close();

    // Parse the JSON data
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

    // Check if the JSON document is valid
    if (!jsonDoc.isNull()) {
        // Access the root object
        QJsonObject jsonObj = jsonDoc.object();

        // Access specific values
        QString mosque_id = jsonObj["mosque_id"].toString();
        QString mac = jsonObj["mac"].toString();
        QString name = jsonObj["name"].toString();
        QString country_id = jsonObj["country_id"].toString();
        QString country = jsonObj["country"].toString();
        QString id_city = jsonObj["id_city"].toString();
        QString street = jsonObj["street"].toString();
        QString house_no = jsonObj["house_no"].toString();
        QString zip = jsonObj["zip"].toString();
        QString status = jsonObj["status"].toString();
        QString public_ip = jsonObj["public_ip"].toString();
        QString pry_method = jsonObj["pry_method"].toString();
        QString activation_code = jsonObj["activation_code"].toString();
        QString date_of_start = jsonObj["date_of_start"].toString();

 }


    this->close();
        if(QMessageBox::information(this,"Finish","Setting is performed successfully",QMessageBox::Ok)==QMessageBox::Ok){
            this->close();
            MainWindow *w= new MainWindow;
            w->showFullScreen();
            w->show();
        }

}


void PrivateMode::on_pushCancel_clicked()
{

     Privacysetting Privacysetting;
    this->close();

    Privacysetting.setWindowFlags(Qt::FramelessWindowHint);
    Privacysetting.show();
    Privacysetting.exec();
}

void PrivateMode::on_comboBox_activated(const QString &arg1)
{

}

