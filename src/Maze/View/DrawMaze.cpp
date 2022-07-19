#include "DrawMaze.h"

DrawMaze::DrawMaze(QWidget *parent)
    : QWidget{parent}
{
    windowControl = nullptr;
}

void DrawMaze::setController(s21::Controller *other) {
    windowControl = other;
}

void DrawMaze::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    if (isMazeExists) {
        QPainter myPainter(this);
        myPainter.setPen(QPen(Qt::red, 2));
        double stepY = 500.0 / windowControl->getMRows();
        double stepX = 500.0 / windowControl->getMCols();
        double y1 = cell;
        myPainter.drawLine(cell, cell, stepX * windowControl->getMCols() + cell, cell);
        myPainter.drawLine(cell, cell, cell, stepY * windowControl->getMRows() + cell);
        for (int i = 0; i < windowControl->getMRows(); i++) {
            y1 += stepY;
            double x1 = cell;
            for (int j = 0; j < windowControl->getMCols(); j++) {
                x1 += stepX;
                if (windowControl->getRight(i, j)) {
                    myPainter.drawLine(x1, y1, x1, y1 - stepY);
                }
                if (windowControl->getBottom(i, j)) {
                    myPainter.drawLine(x1, y1, x1 - stepX, y1);
                }
            }
        }
        if (isPathExists) {
            myPainter.setPen(QPen(Qt::green, 2));
            int k = 0;
            int h1 = (cell + stepX) + (stepX * windowControl->getRoadValH(k)) - (stepX / 2);
            int v1 = (cell + stepY) + (stepY * windowControl->getRoadValV(k)) - (stepY / 2);
            for (k = 1; k < windowControl->getCount(); k++) {
                int h2 = (cell + stepX) + (stepX * windowControl->getRoadValH(k)) - (stepX / 2);
                int v2 = (cell + stepY) + (stepY * windowControl->getRoadValV(k)) - (stepY / 2);
                myPainter.drawLine(h1, v1, h2, v2);
                h1 = h2;
                v1 = v2;
            }
            isPathExists = false;
        }
    }
}

void DrawMaze::openButton_clicked() {
    QString fileName =
    QFileDialog::getOpenFileName(this, "Choose a file", "*.txt", "Labirinth files (*.txt)");
    if (fileName != "") {
        windowControl->initModel(fileName.toStdString());
        isMazeExists = true;
        DrawMaze::update();
    }
}

void DrawMaze::saveButton_clicked() {
    if (!isMazeExists) {
        throw std::invalid_argument("ERROR::There is no Maze!");
    } else {
        QString fileName =
        QFileDialog::getSaveFileName(this, "Save to a file (*.txt)", "./", "Textfiles (*.txt)");
        if (fileName != "") {
            windowControl->saveToFile(fileName);
        }
    }
}

void DrawMaze::generateButton_clicked(int mHeight, int mWidth) {
    if (mHeight > 1 && mWidth > 1 && mHeight < 51 && mWidth < 51) {
        windowControl->generateMaze(mHeight, mWidth);
        isMazeExists = true;
        DrawMaze::update();
    } else {
        throw std::out_of_range("ERROR::Wrong size!");
    }
}

bool DrawMaze::checkPathRange(int h1, int h2, int v1, int v2) {
    bool result = true;
    if (h1 < 0 || h2 < 0 || v1 < 0 || v2 < 0) {
        result = false;
    }
    if (h1 >= windowControl->getMCols() || h2 >= windowControl->getMCols()
    || v1 >= windowControl->getMRows() || v2 >= windowControl->getMRows()) {
        result = false;
    }
    return result;
}

void DrawMaze::findingPath(int v1, int h2, int h1, int v2) {
    if (isMazeExists && checkPathRange(h1, h2, v1, v2)) {
        windowControl->myPath = new s21::FindPath(&windowControl->getModel());
        windowControl->myPath->fillPath(v1, h1);
        windowControl->myPath->waveAlhoritm(v2, h2);
        isPathExists = true;
        DrawMaze::update();
    } else {
        throw std::out_of_range("ERROR::Wrong path!");
    }
}
