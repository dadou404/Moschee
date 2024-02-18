#include "mycombo.h"

class MyComboBox : public QComboBox
    {
        Q_OBJECT

    public:
        explicit MyComboBox(QWidget *parent = 0) : QComboBox(parent){
            setEditable(true);
            completer()->setCompletionMode(QCompleter::PopupCompletion);
            connect(lineEdit(), SIGNAL(editingFinished()), this, SLOT(removeOldestRow()));
        }

        //On Windows this is not needed as long as the combobox is editable
        //This is untested since I don't have Linux
        void showPopup(){
            QComboBox::showPopup();
            QWidget *popup = this->findChild<QFrame*>();
            popup->move(popup->x(), popup->y()+popup->height());
        }

    private slots:
        void removeOldestRow(){
            if(count() == 6)
                removeItem(0);
        }
    };


