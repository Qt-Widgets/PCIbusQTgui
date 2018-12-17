#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view.h"
#include "device.h"
#include "pci.h"
#include <subwindow.h>
#include"device_signals.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    mainBus = new PCI();
    mainBus->SetClock(20);
    QVector<QString> Signals;
    QVector<QString> SignalsNames;
    DeviceA=new DEVICE("DeviceA");
    DeviceB=new DEVICE("DeviceB");
    int numberOfTransfer=1;
    QVector<int> ByteEnable;
    ByteEnable.append(2);
    MainWindow::WriteTransaction(DeviceA,DeviceB,numberOfTransfer,ByteEnable);
    MainWindow::ReadTransaction(DeviceA,DeviceB,numberOfTransfer);






    Signals.append(mainBus->GetReset());
    Signals.append(mainBus->GetDEVSEL());
    Signals.append(mainBus->GetTRDY());
    Signals.append(mainBus->GetIRDY());
    Signals.append(mainBus->GetCBE());
    Signals.append(mainBus->GetControl_Byte());
    Signals.append(mainBus->GetAD());
    Signals.append(mainBus->GetData());
    Signals.append(mainBus->GetFrame());
    Signals.append(mainBus->GetClk());






    SignalsNames.append("Reset");
    SignalsNames.append("DEVSEL");
    SignalsNames.append("TRDY");
    SignalsNames.append("IRDY");
    SignalsNames.append("CBE");
    SignalsNames.append("Control_Byte");
    SignalsNames.append("AD");
    SignalsNames.append("Data");
    SignalsNames.append("Frame");
    SignalsNames.append("Clk");
    Graph=new View(0,Signals,SignalsNames,10);
    Graph->show();
}


void MainWindow::ReadTransaction(DEVICE *Initiator, DEVICE *Target, int numberOfTransfers)
{
    bool endtransaction =false;
    int dataCounter=0;
    for(int mainCounter =1;mainCounter<20*2;mainCounter++)
    {
        if(mainCounter%2==0 && mainCounter!=0) //negative clock edge
        {
            if(mainBus->GetFrameBit()=='1' && !endtransaction) // begin transaction
            {
                mainBus->SetFrame("0");
                mainBus->SetAD("/1");
                mainBus->Setdata("/"+Target->GetDeviceName());
                mainBus->SetCBE("/1");
                mainBus->SetControl_Byte("/Read");
                mainBus->SetPreviousBit("TRDY/IRDY/DEVSEL/Reset/");
            }
            // to detrmine READ OR WRITE
            // the SET IRDY low
            else if(mainBus->GetFrameBit()=='0' && mainBus->GetControl_ByteBit()=="Read")
            {
                mainBus->SetAD("/1");
                mainBus->Setdata("/x");
                mainBus->SetIRDY("0");
                mainBus->SetDEVSEL("0");
                mainBus->SetCBE("/1");
                mainBus->SetControl_Byte("/x");
                mainBus->SetPreviousBit("Frame/TRDY/Reset/");
            }
            // to make target ready and begin transaction since READ transaction and
            // the transacton will begin when both TRDY and IRDY are low
            //Target put the data on the dataline
            else if(mainBus->GetFrameBit()=='0' && mainBus->GetDataBit()=="x" && mainBus->GetIRDYBit()=='0')
            {
                mainBus->SetAD("/1");
                mainBus->Setdata("/"+Target->GetMemoryWord(dataCounter));
                mainBus->SetTRDY("0");
                Initiator->SetMemoryWord(Target->GetMemoryWord(dataCounter),dataCounter);
                numberOfTransfers--;
                dataCounter++;
                if(numberOfTransfers==0)
                {
                   mainBus->SetFrame("1");
                   endtransaction=true;
                   mainBus->SetPreviousBit("CBE/IRDY/DEVSEL/Reset/");
                }
                else
                   mainBus->SetPreviousBit("Frame/CBE/IRDY/DEVSEL/Reset/");
            }
            // if multiple data transfers
            // and if number of transfer reach zero make Frame high
            else if(mainBus->GetFrameBit()=='0' && mainBus->GetIRDYBit()=='0' && mainBus->GetTRDYBit()=='0' && numberOfTransfers!=0)
            {
                 mainBus->SetAD("/1");
                 mainBus->Setdata("/"+Target->GetMemoryWord(dataCounter));
                 Initiator->SetMemoryWord(Target->GetMemoryWord(dataCounter),dataCounter);
                 numberOfTransfers--;
                 dataCounter++;
                 if(numberOfTransfers==0)
                 {
                    mainBus->SetFrame("1");
                    endtransaction=true;
                    mainBus->SetPreviousBit("CBE/IRDY/TRDY/DEVSEL/Reset/");
                 }
                 else
                    mainBus->SetPreviousBit("Frame/CBE/IRDY/TRDY/DEVSEL/Reset/");

            }
            // finish the transaction
            else if(mainBus->GetFrameBit()=='1' && mainBus->GetIRDYBit()=='0' && mainBus->GetTRDYBit()=='0')
            {
                mainBus->SetAD("/1");
                mainBus->Setdata("/x");
                mainBus->SetIRDY("1");
                mainBus->SetTRDY("1");
                mainBus->SetDEVSEL("1");
                mainBus->SetPreviousBit("Frame/CBE/Reset/");
                break;
            }
        }
        else //positive clock edge
        {
            mainBus->SetPreviousBit("Frame/AD/CBE/IRDY/TRDY/DEVSEL/Reset/");

        }
    }
    return ;
}

void MainWindow::WriteTransaction(DEVICE *Initiator, DEVICE *Target, int numberOfTransfers,QVector<int> ByteEnable){
    bool endtransaction =false;
    int dataCounter=0;
    for(int mainCounter =1;mainCounter<20+numberOfTransfers;mainCounter++)
    {
        if(mainCounter%2==0 && mainCounter!=0) //negative clock edge
        {
            if(mainBus->GetFrameBit()=='1' && !endtransaction) // begin transaction
            {
                mainBus->SetFrame("0");
                mainBus->SetAD("/1");
                mainBus->Setdata("/"+Target->GetDeviceName());
                mainBus->SetCBE("/1");
                mainBus->SetControl_Byte("/Write");
                mainBus->SetPreviousBit("TRDY/IRDY/DEVSEL/Reset/");
            }
            // to detrmine READ OR WRITE
            // the SET IRDY low
            else if(mainBus->GetFrameBit()=='0' && mainBus->GetControl_ByteBit()=="Write")
            {
                mainBus->SetAD("/1");
                mainBus->Setdata("/"+Initiator->GetMemoryByte(dataCounter,ByteEnable[dataCounter]));
                mainBus->SetIRDY("0");
                mainBus->SetTRDY("0");
                mainBus->SetDEVSEL("0");
                mainBus->SetCBE("/1");
                mainBus->SetControl_Byte("/"+QString::number(ByteEnable[dataCounter]));

                Target->SetMemoryByte(Initiator->GetMemoryByte(dataCounter,ByteEnable[dataCounter]),dataCounter,ByteEnable[dataCounter]);
                numberOfTransfers--;
                dataCounter++;
                if(numberOfTransfers==0)
                {
                   mainBus->SetFrame("1");
                   endtransaction=true;
                   mainBus->SetPreviousBit("Reset/");
                }
                else
                   mainBus->SetPreviousBit("Frame/Reset/");
            }
            // if multiple data transfers
            // and if number of transfer reach zero make Frame high
            else if(mainBus->GetFrameBit()=='0' && mainBus->GetIRDYBit()=='0' && mainBus->GetTRDYBit()=='0' && numberOfTransfers!=0)
            {
                 mainBus->SetAD("/1");
                 mainBus->Setdata("/"+Initiator->GetMemoryByte(dataCounter,ByteEnable[dataCounter]));
                 Target->SetMemoryByte(Initiator->GetMemoryByte(dataCounter,ByteEnable[dataCounter]),dataCounter,ByteEnable[dataCounter]);
                 mainBus->SetCBE("/1");
                 mainBus->SetControl_Byte("/"+QString::number(ByteEnable[dataCounter]));
                 numberOfTransfers--;
                 dataCounter++;
                 if(numberOfTransfers==0)
                 {
                    mainBus->SetFrame("1");
                    endtransaction=true;
                    mainBus->SetPreviousBit("IRDY/TRDY/DEVSEL/Reset/");
                 }
                 else
                    mainBus->SetPreviousBit("Frame/IRDY/TRDY/DEVSEL/Reset/");

            }
            // finish the transaction
            else if(mainBus->GetFrameBit()=='1' && mainBus->GetIRDYBit()=='0' && mainBus->GetTRDYBit()=='0')
            {
                mainBus->SetAD("/1");
                mainBus->Setdata("/x");
                mainBus->SetIRDY("1");
                mainBus->SetTRDY("1");
                mainBus->SetDEVSEL("1");
                mainBus->SetCBE("/1");
                mainBus->SetControl_Byte("/x");
                mainBus->SetPreviousBit("Frame/Reset/");
                break;
            }
        }
        else //positive clock edge
        {
            mainBus->SetPreviousBit("Frame/AD/CBE/IRDY/TRDY/DEVSEL/Reset/");

        }
    }
    return ;
}

void MainWindow::on_DevA_spinBox_editingFinished()
{
    SubWindow = new subWindow(this,ui->DevA_spinBox->value(),"DEVICE A");
    SubWindow->setModal(true);
    SubWindow->setWindowTitle("DEVICE A");
    if(ui->DevA_spinBox->value() != 0){

        DevA.set_numOfTrans(QString::number(ui->DevA_spinBox->value()));

        ui->DevA_spinBox->blockSignals(true);
         ui->DevA_spinBox->setEnabled(false);
         SubWindow->exec();
         ui->DevA_spinBox->blockSignals(false);
    }
}

void MainWindow::on_DevB_spinBox_editingFinished()
{
    SubWindow = new subWindow(this,ui->DevB_spinBox->value(),"DEVICE B");
    SubWindow->setModal(true);
    SubWindow->setWindowTitle("DEVICE B");
    if(ui->DevB_spinBox->value() != 0){
        ui->DevB_spinBox->blockSignals(true);
        ui->DevB_spinBox->setEnabled(false);
        SubWindow->exec();
        ui->DevB_spinBox->blockSignals(false);
    }
}

void MainWindow::on_DevC_spinBox_editingFinished()
{
    SubWindow = new subWindow(this,ui->DevC_spinBox->value(),"DEVICE C");
    SubWindow->setModal(true);
    SubWindow->setWindowTitle("DEVICE C");
    if(ui->DevC_spinBox->value() != 0){
        ui->DevC_spinBox->blockSignals(true);
        ui->DevC_spinBox->setEnabled(false);
        SubWindow->exec();
        ui->DevC_spinBox->blockSignals(false);
    }
}

void MainWindow::on_DevD_spinBox_editingFinished()
{
    SubWindow = new subWindow(this,ui->DevD_spinBox->value(),"");
    SubWindow->setModal(true);
    SubWindow->setWindowTitle("DEVICE D");
    if(ui->DevD_spinBox->value() != 0){
        ui->DevD_spinBox->blockSignals(true);
        ui->DevD_spinBox->setEnabled(false);
        SubWindow->exec();
        ui->DevD_spinBox->blockSignals(false);
    }
}

void MainWindow::on_DevA_InitiatorRadio_clicked()
{
   DevA.set_masterSelect("A");

}
