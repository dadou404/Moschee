#ifndef DYNAMICFONTSIZELABEL_H
#define DYNAMICFONTSIZELABEL_H

#include <QLabel>
#include <QColor>
#include <QSize>

class DynamicFontSizeLabel : public QLabel {
    Q_OBJECT

public:
    explicit DynamicFontSizeLabel(QWidget* parent = NULL, Qt::WindowFlags f = Qt::WindowFlags());

    ~DynamicFontSizeLabel() {}

    static float getWidgetMaximumFontSize(QWidget *widget, QString text);

    /* This method overwrite stylesheet */
    void setTextColor(QColor color);
    QColor getTextColor();
    void setTextAndColor(const QString &text, QColor color = QColor::Invalid);
signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
    QColor textColor;


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

    // QWidget interface
public:
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
};

#endif // DYNAMICFONTSIZELABEL_H
