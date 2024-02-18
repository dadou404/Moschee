#ifndef TIMESETTING_H
#define TIMESETTING_H

#include <QDialog>

namespace Ui {
class TimeSetting;
}

class TimeSetting : public QDialog
{
    Q_OBJECT

public:
    explicit TimeSetting(QWidget *parent = 0);
    ~TimeSetting();

private slots:
    void on_NextPush_clicked();

private:
    Ui::TimeSetting *ui;
};

#endif // TIMESETTING_H
