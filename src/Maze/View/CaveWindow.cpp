#include "CaveWindow.h"
#include "ui_CaveWindow.h"
namespace s21{
CaveWindow::CaveWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CaveWindow),
    _currentCave(5,5,50,2,3)
{
    ui->setupUi(this);
    _keyCtrl1=new QShortcut(this);
    _keyCtrl1->setKey(Qt::CTRL | Qt::Key::Key_1);
    connect(_keyCtrl1,&QShortcut::activated,this,&CaveWindow::closeWindow);
}

CaveWindow::~CaveWindow()
{
    delete ui;
}
void CaveWindow::closeWindow(){
    this->close();
    emit openMazeWindow();
}


void CaveWindow::on_caveGenerateButtom_clicked()
{
    _currentCave=Cave(ui->spinBoxWidthCave->value(),
                      ui->spinBoxHeightCave->value(),
                      ui->SpinBoxChance->value(),
                      ui->spinBoxLife->value(),
                      ui->spinBoxDeath->value());
    ui->DrawWidget->updateCave(&_currentCave);
}


void CaveWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index==1){
        ui->caveNextStepButtom->setText(QString("Start"));
    } else {
        ui->caveNextStepButtom->setText(QString("Next step"));
    }
}


void CaveWindow::on_caveNextStepButtom_clicked()
{
    if(ui->caveNextStepButtom->text()==QString("Next step")){
        _currentCave.update();
        ui->DrawWidget->updateCave(&_currentCave);
    } else if (ui->caveNextStepButtom->text()==QString("Start")) {
        ui->caveNextStepButtom->setText(QString("Stop"));
        tmr = new QTimer();
        tmr->setInterval(ui->doubleSpinBoxTime->value()*1000);
        connect(tmr, &QTimer::timeout, this, &CaveWindow::update);
        tmr->start();
    } else {
        ui->caveNextStepButtom->setText(QString("Start"));
        delete tmr;
    }
}

void CaveWindow::on_caveOpenFile_clicked()
{
  std::string fileName =
          QFileDialog::getOpenFileName(this, "Save to a file (*.txt)", "./", "Textfiles (*.txt)").toStdString();
  if(fileName!=""){
      try {
          _currentCave=Cave(fileName,ui->spinBoxLife->value(),ui->spinBoxDeath->value());
          ui->DrawWidget->updateCave(&_currentCave);
      }  catch (std::exception& e) {
          ErrorDialog errorWindow(e);
          errorWindow.setModal(true);
          errorWindow.exec();
      }
  }
}

void CaveWindow::update()
{
    _currentCave.update();
    ui->DrawWidget->updateCave(&_currentCave);
    tmr->start();
}


void CaveWindow::on_caveSaveToFile_clicked()
{
    std::string fileName=QFileDialog::getSaveFileName(this, "Save to a file (*.txt)", "./", "Textfiles (*.txt)").toStdString();
    if(fileName!=""){
        try {
            _currentCave.save(fileName);
        }  catch (std::exception& e) {
            ErrorDialog errorWindow(e);
            errorWindow.setModal(true);
            errorWindow.exec();
        }
    }
}


void CaveWindow::on_spinBoxLife_valueChanged(int arg1)
{
    _currentCave.setBirth(arg1);
}


void CaveWindow::on_spinBoxDeath_valueChanged(int arg1)
{
    _currentCave.setDeath(arg1);
}

};
