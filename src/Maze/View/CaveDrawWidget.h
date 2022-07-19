#ifndef CAVEDRAWWIDGET_H
#define CAVEDRAWWIDGET_H
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QDebug>
#include "../Model/Cave.h"
class CaveDrawWidget: public QWidget
{
public:
    explicit CaveDrawWidget(QWidget* parent=nullptr);
    void clearWidget();
    void updateCave(Cave* cave);
protected:
    void paintEvent(QPaintEvent *event)override;
private:
    QImage _cell;
};

#endif // CAVEDRAWWIDGET_H
