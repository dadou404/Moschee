#ifndef ACTIVATIONSETTINGS_H
#define ACTIVATIONSETTINGS_H

#include <QDialog>

namespace Ui {
class ActivationSettings;
}

class ActivationSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ActivationSettings(QWidget *parent = 0);
    ~ActivationSettings();

private slots:
    void on_Offline_Activation_clicked();

    void on_NextButton_clicked();

private:
    Ui::ActivationSettings *ui;
};

#endif // ACTIVATIONSETTINGS_H
