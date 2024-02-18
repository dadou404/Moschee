#ifndef PRAYERMETHOD_H
#define PRAYERMETHOD_H
#include"initlializationsettingfile.h"
#include <QDialog>

namespace Ui {
class PrayerMethod;
}

class PrayerMethod : public QDialog
{
    Q_OBJECT

public:
    explicit PrayerMethod(QWidget *parent = 0);
    initlializationSettingFile StoreSettings;

    ~PrayerMethod();

private slots:
    void on_Next_clicked();

    void on_BackPush_clicked();

private:
    Ui::PrayerMethod *ui;
};

#endif // PRAYERMETHOD_H
