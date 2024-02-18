#ifndef WIRELESSLOG_H
#define WIRELESSLOG_H

#include <QDialog>
#include<QDebug>

namespace Ui {
class wirelesslog;
}

class wirelesslog : public QDialog
{
    Q_OBJECT

public:
    explicit wirelesslog(QWidget *parent = nullptr);
    ~wirelesslog();

private:
    Ui::wirelesslog *ui;
private slots:
    void on_keyboard_clicked();
    void on_keyboard_2_clicked();
    void on_keyboard_3_clicked();
};

#endif // WIRELESSLOG_H
