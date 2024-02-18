#include "qcomboc.h"

class ComboBox: public QComboBox{

  public:
    using QComboBox::QComboBox;
public:
    void showPopup(){
        QComboBox::showPopup();
        QPoint pos = mapToGlobal(QPoint(0,height()));
        view()->parent
    }

};
