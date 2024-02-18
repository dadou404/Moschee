#ifndef F_PRIVACYSETTING_H
#define F_PRIVACYSETTING_H

#include <QDialog>
#include<QLabel>
#include "initlializationsettingfile.h"
namespace Ui {
class privacysetting;
}

class PrivacySetting : public QDialog
{
    Q_OBJECT

public:
    explicit PrivacySetting(QWidget *parent = 0);
    initlializationSettingFile StoreSettings;
    void update_internet_inrerfaces();

    ~PrivacySetting();

private slots:

private:
    Ui::privacysetting *ui;
};
#endif // F_PRIVACYSETTING_H


