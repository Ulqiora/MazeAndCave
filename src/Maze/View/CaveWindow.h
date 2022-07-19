#ifndef CAVEWINDOW_H
#define CAVEWINDOW_H

#include <QMainWindow>
#include <QShortcut>
#include <QFileDialog>
#include <QTimer>
#include <QTime>
#include "../Model/Cave.h"
#include "ErrorDialog.h"

namespace Ui {
class CaveWindow;
}

namespace s21{
class CaveWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit CaveWindow(QWidget *parent = nullptr);
    ~CaveWindow();
private slots:
    void closeWindow();
    void on_caveGenerateButtom_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_caveNextStepButtom_clicked();

    void on_caveOpenFile_clicked();
    void update();
    void on_caveSaveToFile_clicked();

    void on_spinBoxLife_valueChanged(int arg1);

    void on_spinBoxDeath_valueChanged(int arg1);

signals:
    void openMazeWindow();
private:
    Ui::CaveWindow *ui;
    QShortcut* _keyCtrl1;
    Cave _currentCave;
    QTimer *tmr;
};
};    //    namespace s21
#endif // CAVEWINDOW_H
