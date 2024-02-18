#ifndef WELCOMEFORM_H
#define WELCOMEFORM_H

#include <QDialog>
#include<QLabel>
#include "initlializationsettingfile.h"
namespace Ui {
class WelcomeForm;
}

class WelcomeForm : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeForm(QWidget *parent = 0);
    initlializationSettingFile StoreSettings;
    void update_internet_inrerfaces();

    ~WelcomeForm();

private slots:
    void on_NextStepPushButton_clicked();


    void on_Mouse_clicked();

    void on_VNC_Remote_clicked();
    void on_Android_app_clicked();

    void on_on_screen_keyboard_clicked();

    void on_Add_Network_Button_clicked();

    void on_Erease_all_Button_clicked();

    void on_Connect_Button_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::WelcomeForm *ui;
};

#endif // WELCOMEFORM_H
