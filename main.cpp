#include "mainwindow.h"
#include "privatemode.h"
#include <QApplication>
#include"screeninformation.h"
#include<QDebug>
#include<QInputDialog>
#include"initlializationsettingfile.h"
#include"welcomeform.h"
#include<QTranslator>
#include<QSettings>
#include<QApplication>
#include<QCoreApplication>
int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
  //  QApplication b(argc, argv);


    initlializationSettingFile fg;


    QString Dir_setting_file=QCoreApplication::applicationDirPath()+"/Settings.ini";
    QSettings *Settings_Pro = new QSettings(Dir_setting_file, QSettings::IniFormat);
    qDebug()<<Dir_setting_file;
    bool Exist = fg.fileExists(Dir_setting_file);
    qDebug()<<Exist;

       if(Exist==false){

           WelcomeForm Welcom;
           Welcom.show();
           Welcom.setWindowFlags(Qt::FramelessWindowHint);
           Welcom.exec();
  //          return b.exec();

}else{
            MainWindow w;
            w.showFullScreen();
            w.show();
            return a.exec();

}
}
