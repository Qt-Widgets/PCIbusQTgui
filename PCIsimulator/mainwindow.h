#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "view.h"
#include "pci.h"
#include "device.h"
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
    void ReadTransaction(DEVICE *A,DEVICE *B,int numberOfTransfers);
    void WriteTransaction(DEVICE *A,DEVICE *B,int numberOfTransfers,QVector<int> ByteEnable);

    void on_DevA_spinBox_editingFinished();

    void on_DevB_spinBox_editingFinished();

    void on_DevC_spinBox_editingFinished();

    void on_DevD_spinBox_editingFinished();


private:
    Ui::MainWindow *ui;
    View * Graph;
    QVector<QString> Signals;
    QVector<QString> SignalsNames;
    PCI *mainBus;
    DEVICE *DeviceA;
    DEVICE *DeviceB;
    DEVICE *DeviceC;
    DEVICE *DeviceD;
    subWindow *SubWindow;


};

#endif // MAINWINDOW_H
