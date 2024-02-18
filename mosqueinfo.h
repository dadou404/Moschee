#ifndef MOSQUEINFO_H
#define MOSQUEINFO_H
#include"initlializationsettingfile.h"

#include <QDialog>

namespace Ui {
class MosqueInfo;
}

class MosqueInfo : public QDialog
{
    Q_OBJECT

public:
    explicit MosqueInfo(QWidget *parent = 0);
    initlializationSettingFile StoreSettings;

    ~MosqueInfo();

private slots:
    void on_NextPush_clicked();

   void on_pushButton_clicked();

   void on_BackPush_clicked();

private:
    Ui::MosqueInfo *ui;
};

#endif // MOSQUEINFO_H
