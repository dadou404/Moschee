#ifndef REGION_H
#define REGION_H
#include "databaseconnection.h"
#include"initlializationsettingfile.h"
#include "welcomeform.h"
#include <QDialog>
#include<QComboBox>
namespace Ui {
class Region;
}

class Region : public QDialog
{
    Q_OBJECT

public:
    explicit Region(QWidget *parent = 0);
    DatabaseConnection instant;
    int Lang_Index=0;
    QString setLang;
    QComboBox CountryListBox;
    initlializationSettingFile Settings;

    ~Region();

private slots:
     void on_CountryListBox_currentTextChanged(const QString &arg1);

     void on_CityListBox_currentTextChanged(const QString &arg1);

     void on_ChangingLanLonPush_clicked();

     void on_NextPush_clicked();

     void on_Language_List_currentIndexChanged(int index);

     void on_BackPush_clicked();

private:
    Ui::Region *ui;
};

#endif // REGION_H
