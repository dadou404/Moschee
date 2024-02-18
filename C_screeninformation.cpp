
#include "screeninformation.h"
#include<QDebug>
#include<QtGui>
#include<QSize>

ScreenInformation::ScreenInformation()
{

}
QSize ScreenInformation::ScreenSize(){

 QRect rec = QApplication::desktop()->screenGeometry();

 QSize size = qApp->screens()[0]->size();

    return size;
}
ScreenInformation::~ScreenInformation(){

}
