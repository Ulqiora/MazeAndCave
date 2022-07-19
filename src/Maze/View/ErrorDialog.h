#ifndef SRC_MAZE_VIEW_ERRORDIALOG_H_
#define SRC_MAZE_VIEW_ERRORDIALOG_H_

#include <QDialog>

namespace Ui {
class ErrorDialog;
}


class ErrorDialog : public QDialog {
    Q_OBJECT

 public:
    explicit ErrorDialog(std::exception& error, QWidget *parent = nullptr);
    ~ErrorDialog();

 private:
    Ui::ErrorDialog *ui;
};

#endif  // SRC_MAZE_VIEW_ERRORDIALOG_H_
