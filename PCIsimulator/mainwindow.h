#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "view.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_DevA_InitiatorRadio_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    View * Graph;

};

#endif // MAINWINDOW_H
