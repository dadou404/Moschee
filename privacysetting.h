#ifndef PRIVACYSETTING_H
#define PRIVACYSETTING_H

#include <QDialog>

namespace Ui {
class Privacysetting;
}

class Privacysetting : public QDialog
{
    Q_OBJECT

public:
    explicit Privacysetting(QWidget *parent = nullptr);
    ~Privacysetting();

private slots:
    void on_pushPrivate_clicked();

    void on_pushPublic_clicked();

private:
    Ui::Privacysetting *ui;
};

#endif // PRIVACYSETTING_H
