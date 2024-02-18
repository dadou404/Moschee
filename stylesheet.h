#ifndef STYLESHEET_H
#define STYLESHEET_H
#include<QString>

class StyleSheet
{
public:
    StyleSheet();

 QString ParsingCssFile(QString);
 QString BackgroundChanging(QString path);
};

#endif // STYLESHEET_H
