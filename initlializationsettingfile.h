#ifndef INITLIALIZATIONSETTINGFILE_H
#define INITLIALIZATIONSETTINGFILE_H
#include<QFileInfo>
#include<QSettings>
#include<QCoreApplication>

class initlializationSettingFile
{
public:
    initlializationSettingFile();
    QString Dir_setting_file=QCoreApplication::applicationDirPath()+"/Settings.ini";
    QSettings *Settings_Pro = new QSettings(Dir_setting_file, QSettings::IniFormat);
    bool fileExists(QString Path);
    void StoreSettings(QString Group, QString Tag ,QVariant Value);
    QVariant ReadSettings(QString Group, QString Tag);

private:
};

#endif // INITLIALIZATIONSETTINGFILE_H
