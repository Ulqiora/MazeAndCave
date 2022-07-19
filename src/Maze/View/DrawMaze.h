#ifndef SRC_MAZE_VIEW_DRAWMAZE_H_
#define SRC_MAZE_VIEW_DRAWMAZE_H_

#include <QWidget>
#include <QPainter>
#include <QFileDialog>
#include "../Controller/Controller.h"

class DrawMaze : public QWidget {
    Q_OBJECT
 public:
    explicit DrawMaze(QWidget *parent = nullptr);
    void setController(s21::Controller *other);
    bool checkPathRange(int x1, int x2, int y1, int y2);
    void findingPath(int v1, int h2, int h1, int v2);
    void openButton_clicked();
    void saveButton_clicked();
    void generateButton_clicked(int mHeight, int mWidth);

 protected:
    void paintEvent(QPaintEvent *event);

 private:
    s21::Controller* windowControl;
    bool isMazeExists = false;
    bool isPathExists = false;
    const double cell = 1.0;
};

#endif  // SRC_MAZE_VIEW_DRAWMAZE_H_
