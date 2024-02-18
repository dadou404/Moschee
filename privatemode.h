#ifndef PRIVATEMODE_H
#define PRIVATEMODE_H
#include <QSettings>
#include <QDialog>
#include"initlializationsettingfile.h"

namespace Ui {
class PrivateMode;
}

class PrivateMode : public QDialog
{
    Q_OBJECT

public:
    explicit PrivateMode(QWidget *parent = nullptr);
    initlializationSettingFile StoreSettings;

    ~PrivateMode();

private slots:
    void on_pushOk_clicked();

    void on_pushCancel_clicked();

    void on_comboBox_activated(const QString &arg1);

private:
    Ui::PrivateMode *ui;
};

#endif // PRIVATEMODE_H
