#include "privacysetting.h"
#include "ui_privacysetting.h"
#include<QInputDialog>
#include<QMessageBox>
#include"region.h"
#include "privatemode.h"
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

Privacysetting::Privacysetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Privacysetting)
{
    ui->setupUi(this);
}

Privacysetting::~Privacysetting()
{
    delete ui;
}

void Privacysetting::on_pushPrivate_clicked()
{

    this->close();
    PrivateMode PrivateMode;
    PrivateMode.setWindowFlags(Qt::FramelessWindowHint);
    PrivateMode.show();
    PrivateMode.exec();
}


void Privacysetting::on_pushPublic_clicked()
{
    this->close();
    Region Region;
    Region.setWindowFlags(Qt::FramelessWindowHint);
    Region.show();
    Region.exec();
}

