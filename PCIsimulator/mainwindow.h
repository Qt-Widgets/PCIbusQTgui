#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "view.h"
#include "pci.h"
#include "device.h"
#include "subwindow.h"
#include "device_signals.h"



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





    void on_DevA_ByteIndex_currentTextChanged(const QString &arg1);

    void on_DevB_ByteIndex_currentTextChanged(const QString &arg1);

    void on_DevC_ByteIndex_currentTextChanged(const QString &arg1);

    void on_DevD_ByteIndex_currentTextChanged(const QString &arg1);

    void on_Submit_clicked(bool checked);



    void on_DevA_RowIndex_currentIndexChanged(const QString &arg1);

    void on_DevB_RowIndex_currentIndexChanged(const QString &arg1);

    void on_DevC_RowIndex_currentIndexChanged(const QString &arg1);

    void on_DevD_RowIndex_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    View * Graph;
    QVector<QString> Signals;
    QVector<QString> SignalsNames;
    PCI *mainBus;

    subWindow *SubWindow;

    DEVICE *DeviceA;
    DEVICE *DeviceB;
    DEVICE *DeviceC;
    DEVICE *DeviceD;

    //when a device says that he is an intiator .. it will be stored in this Queue
    QVector <DEVICE*> MastersSelect;

    //4 Devices signals in which options of each device is stored
    Device_Signals *devA_main,*devB_main,*devC_main,*devD_main;
    QVector <int> delay;

};

#endif // MAINWINDOW_H
