#ifndef MYCOMBO_H
#define MYCOMBO_H
#include <QComboBox>
class MyComboBox : public QComboBox
{
    Q_OBJECT

public:

    //On Windows this is not needed as long as the combobox is editable
    //This is untested since I don't have Linux
    void showPopup(){
        QComboBox::showPopup();
        QWidget *popup = this->findChild<QFrame*>();
        popup->move(popup->x(), popup->y()+popup->height());
    }



};

#endif // MYCOMBO_H
