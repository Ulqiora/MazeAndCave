#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(s21::CaveWindow* secondWindow,s21::Controller* mainControl, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->drawMazeArea->setController(mainControl);
    _windowCave=secondWindow;
    _keyCtrl2=new QShortcut(this);
    _keyCtrl2->setKey(Qt::CTRL | Qt::Key::Key_2);
    connect(_keyCtrl2,SIGNAL(activated()),this,SLOT(openCaveWindow()));
    connect(_windowCave,&s21::CaveWindow::openMazeWindow,this,&MainWindow::show);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_openButton_clicked() {
    try {
        ui->drawMazeArea->openButton_clicked();
    }
    catch(std::exception& error) {
        ErrorDialog errorWindow(error);
        errorWindow.setModal(true);
        errorWindow.exec();
    }
}

void MainWindow::on_generateButton_clicked() {
    int mHeight = ui->mazeHeightBox->text().toInt();
    int mWidth = ui->mazeWidthBox->text().toInt();
    try {
        ui->drawMazeArea->generateButton_clicked(mHeight, mWidth);
    }
    catch (std::exception& error) {
        ErrorDialog errorWindow(error);
        errorWindow.setModal(true);
        errorWindow.exec();
    }
}

void MainWindow::on_findPathButton_clicked() {
    bool b1, b2, b3, b4;
    int v1, h2, h1, v2;
    v1 = ui->vertBeginBox->text().toInt(&b1);
    h2 = ui->horizEndBox->text().toInt(&b2);
    h1 = ui->horizBeginBox->text().toInt(&b3);
    v2 = ui->vertEndBox->text().toInt(&b4);
    if (b1 && b2 && b3 && b4) {
        try {
            ui->drawMazeArea->findingPath(v1, h2, h1, v2);
        }
        catch(std::exception& error) {
            ErrorDialog errorWindow(error);
            errorWindow.setModal(true);
            errorWindow.exec();
        }
    }
}

void MainWindow::on_saveButton_clicked()
{
    try {
        ui->drawMazeArea->saveButton_clicked();
    }
    catch(std::exception& error) {
        ErrorDialog errorWindow(error);
        errorWindow.setModal(true);
        errorWindow.exec();
    }
}

void MainWindow::openCaveWindow(){
    _windowCave->show();
    this->close();
}
