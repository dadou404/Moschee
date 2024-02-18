#include "stylesheet.h"
#include"initlializationsettingfile.h"
#include<QDate>
#include<QTextStream>

StyleSheet::StyleSheet()
{
}
QString StyleSheet::ParsingCssFile(QString CssFile){

    QFile styleFile(CssFile);
       styleFile.open(QIODevice::ReadOnly);
       QTextStream textStream(&styleFile);
       QString styleSheet = textStream.readAll();
       styleFile.close();
    //       qDebug()<<styleSheet;
    return styleSheet;
}
QString StyleSheet::BackgroundChanging(QString path){
    int day;
    day= QDate::currentDate().day();
       QString Background="QMainWindow{border-image: url("+path+"/Background/Background"+QVariant(day).toString()+".jpg) 0 0 0 0 stretch stretch;border-width: 0px}";
return Background;
}
