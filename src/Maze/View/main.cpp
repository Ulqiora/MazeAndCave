#include "mainwindow.h"
#include "Maze/Controller/Controller.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    s21::InitMaze myMaze;
    s21::Controller myController(&myMaze);
    s21::CaveWindow caveWindow;
    MainWindow w(&caveWindow,&myController);
    w.show();
    return a.exec();
}
