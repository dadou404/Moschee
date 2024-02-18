#ifndef SCREENINFORMATION_H
#define SCREENINFORMATION_H
#include<QScreen>
#include<QtGui>
#include<QApplication>
#include<QDesktopWidget>

class ScreenInformation
{
public:
    ScreenInformation();
    QSize ScreenSize();
    ~ScreenInformation();
private:

};

#endif // SCREENINFORMATION_H
