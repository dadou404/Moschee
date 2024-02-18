#include "initlializationsettingfile.h"
#include<QString>
#include<QCoreApplication>
#include<QDebug>


initlializationSettingFile::initlializationSettingFile()
{

}
bool initlializationSettingFile::fileExists(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}
void initlializationSettingFile::StoreSettings(QString Group, QString Tag, QVariant Value){


    QString GroupwithTag=Group+"/"+Tag;
    Settings_Pro->setValue(GroupwithTag,Value);
      qDebug()<<"Store a vlaue of "<<Tag<<Dir_setting_file<<GroupwithTag;

}
QVariant initlializationSettingFile::ReadSettings(QString Group,QString Tag){

    QString GroupwithTag= Group+"/"+Tag;
    QVariant Var= Settings_Pro->value(GroupwithTag,0);


    return Var;

}
