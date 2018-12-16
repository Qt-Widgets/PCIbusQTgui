#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "view.h"
#include "subwindow.h"
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

    void on_DevA_spinBox_editingFinished();

    void on_DevB_spinBox_editingFinished();

    void on_DevC_spinBox_editingFinished();

    void on_DevD_spinBox_editingFinished();

private:
    Ui::MainWindow *ui;
    View * Graph;
    subWindow *SubWindow;
};

#endif // MAINWINDOW_H
