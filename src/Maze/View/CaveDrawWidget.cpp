#include "CaveDrawWidget.h"

CaveDrawWidget::CaveDrawWidget(QWidget* parent):QWidget(parent)
{
    _cell=QImage(QSize(600, 600), QImage::Format_ARGB32);
}

void CaveDrawWidget::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, _cell, dirtyRect);
}

void CaveDrawWidget::updateCave(Cave* cave){
    clearWidget();
    QPainter painter(&_cell);
    painter.setPen(QPen(Qt::white, 1));
    painter.drawRect(0, 0, 600-1, 600-1);
    painter.setBrush(QBrush(Qt::black));
    for (int i = 0; i < cave->getRows(); i++) {
        for (int j = 0; j < cave->getCols(); j++) {
            if((*cave)(i,j)==Cave::ALIVE)
                painter.drawRect(
                    QRect(QPoint(600.0/cave->getCols()*j,600.0/cave->getRows()*i),
                          QSize(600.0/cave->getCols(), 600.0/cave->getRows())));
        }
    }
    update();
}

void CaveDrawWidget::clearWidget(){
    _cell.fill(QColor(0, 0, 0, 0));
}
