#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "view.h"
#include "pci.h"
#include "device.h"
#include "subwindow.h"
#include "device_signals.h"
#include <QQueue>
#include <QAction>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static int const EXIT_CODE_REBOOT; // for restart
    QAction* actionReboot;


private slots:
    void on_pushButton_clicked();
    void ReadTransaction(DEVICE *A,DEVICE *B);
    void WriteTransaction(DEVICE *A,DEVICE *B);
    void FCFS(int begin,int end);
    void Priority(int begin,int end);
    void SortPriority();
    int findMaster();
    bool masterIsPrior();

    //when no of transaction is determined ... the sub window opens 
    void on_DevA_spinBox_editingFinished();

    void on_DevB_spinBox_editingFinished();

    void on_DevC_spinBox_editingFinished();

    void on_DevD_spinBox_editingFinished();




    //when data of line edit input is changed .. this byte in device memory will be changed to that value 
    void on_DevA_ByteIndex_currentTextChanged(const QString &arg1);

    void on_DevB_ByteIndex_currentTextChanged(const QString &arg1);

    void on_DevC_ByteIndex_currentTextChanged(const QString &arg1);

    void on_DevD_ByteIndex_currentTextChanged(const QString &arg1);

    //this for submit delay button .. when you press this button : delay will be stored in vector of delays , and memory will be updated
    void on_Submit_clicked(bool checked);


    // to show what is stored in memory in each row 
    void on_DevA_RowIndex_currentIndexChanged(const QString &arg1);

    void on_DevB_RowIndex_currentIndexChanged(const QString &arg1);

    void on_DevC_RowIndex_currentIndexChanged(const QString &arg1);

    void on_DevD_RowIndex_currentIndexChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

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
    DEVICE *master;
    QVector<DEVICE*> nonActive;
    QQueue<int> queue;
    QQueue<QString> queueP;
    QQueue<int> queueTime;
    bool beginTransaction;
    bool endTransaction;
    bool gnthigh; // a bool to take the grant from master after frame is low
    int dataCounter;
    bool firstMaster;
    bool allgnt;
    bool otherReq;
    int mainCounter;
    QString nonActiveIndex;
    bool senarioFlag;
    // variables which won't be needed after the inputs are set
    int numberOfTransfers;
    QVector<int> ByteEnable;
    QString Transaction;
    int numberOfTrnsaction;

    //when a device says that he is an intiator .. it will be stored in this Queue
    QQueue <DEVICE*> MastersSelect;

    //4 Devices signals in which options of each device is stored
    Device_Signals *devA_main,*devB_main,*devC_main,*devD_main;
    Device_Signals tempControl;
    QQueue <int> delay;

    Device_Signals*  masterControl;
    QQueue<Device_Signals*> MastersControl;
    DEVICE *masterTarget;
    QVector<Device_Signals*> nonActiveControl;

    int arbiterMoodIndex;

};

#endif // MAINWINDOW_H
