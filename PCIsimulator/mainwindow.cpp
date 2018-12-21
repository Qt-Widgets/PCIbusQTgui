#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view.h"
#include "device.h"
#include "pci.h"
#include <subwindow.h>
#include"device_signals.h"
#include <QDebug>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    DeviceA=new DEVICE("DeviceA");
    DeviceB=new DEVICE("DeviceB");
    DeviceC=new DEVICE("DeviceA");
    DeviceD=new DEVICE("DeviceB");
    devA_main=new Device_Signals();
    devB_main=new Device_Signals();
    devC_main=new Device_Signals();
    devD_main=new Device_Signals();

    ui->DevA_IdleRadio->setChecked(true);
    ui->DevB_IdleRadio->setChecked(true);
    ui->DevC_IdleRadio->setChecked(true);
    ui->DevD_IdleRadio->setChecked(true);
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
    if(ui->DevA_spinBox->value() <=2){

        SubWindow = new subWindow(this,ui->DevA_spinBox->value(),"DEVICE A",devA_main,devB_main,devC_main,devD_main,
                                   DeviceA,DeviceB,DeviceC,DeviceD);
        SubWindow->setModal(true);
        SubWindow->setWindowTitle("DEVICE A");
        if(ui->DevA_spinBox->value() != 0){
            devA_main->set_numOfTrans(ui->DevA_spinBox->value());
            ui->DevA_spinBox->blockSignals(true);
            ui->DevA_spinBox->setEnabled(false);
            SubWindow->exec();
            ui->DevA_spinBox->blockSignals(false);
        }
    }
    else{
         ui->DevA_spinBox->blockSignals(true);
        QMessageBox::warning(this,"Error","Number of Transactions can't be more than 2");
         ui->DevA_spinBox->blockSignals(false);
    }
}

void MainWindow::on_DevB_spinBox_editingFinished()
{
    if(ui->DevB_spinBox->value()<=2){
        SubWindow = new subWindow(this,ui->DevB_spinBox->value(),"DEVICE B",devA_main,devB_main,devC_main,devD_main,
                                   DeviceA,DeviceB,DeviceC,DeviceD);
        SubWindow->setModal(true);
        SubWindow->setWindowTitle("DEVICE B");
        if(ui->DevB_spinBox->value() != 0){
            ui->DevB_spinBox->blockSignals(true);
            ui->DevB_spinBox->setEnabled(false);
            devB_main->set_numOfTrans(ui->DevB_spinBox->value());
            SubWindow->exec();
            ui->DevB_spinBox->blockSignals(false);
        }
    }
    else{
         ui->DevB_spinBox->blockSignals(true);
        QMessageBox::warning(this,"Error","Number of Transactions can't be more than 2");
         ui->DevB_spinBox->blockSignals(false);
    }
}

void MainWindow::on_DevC_spinBox_editingFinished()
{
    if(ui->DevC_spinBox->value()<=2){
        SubWindow = new subWindow(this,ui->DevC_spinBox->value(),"DEVICE C",devA_main,devB_main,devC_main,devD_main,
                                  DeviceA,DeviceB,DeviceC,DeviceD );
        SubWindow->setModal(true);
        SubWindow->setWindowTitle("DEVICE C");
        if(ui->DevC_spinBox->value() != 0){
            ui->DevC_spinBox->blockSignals(true);
            ui->DevC_spinBox->setEnabled(false);
            devC_main->set_numOfTrans(ui->DevC_spinBox->value());
            SubWindow->exec();
            ui->DevC_spinBox->blockSignals(false);
        }
    }
    else{
        ui->DevC_spinBox->blockSignals(true);
        QMessageBox::warning(this,"Error","Number of Transactions can't be more than 2");
         ui->DevC_spinBox->blockSignals(false);
    }
}

void MainWindow::on_DevD_spinBox_editingFinished()
{
    if(ui->DevD_spinBox->value()<=2){
        SubWindow = new subWindow(this,ui->DevD_spinBox->value(),"DEVICE D",devA_main,devB_main,devC_main,devD_main,
                                  DeviceA,DeviceB,DeviceC,DeviceD);
        SubWindow->setModal(true);
        SubWindow->setWindowTitle("DEVICE D");
        if(ui->DevD_spinBox->value() != 0){
            ui->DevD_spinBox->blockSignals(true);
            ui->DevD_spinBox->setEnabled(false);
            devD_main->set_numOfTrans(ui->DevD_spinBox->value());
            SubWindow->exec();
            ui->DevD_spinBox->blockSignals(false);
        }
    }
    else{
         ui->DevD_spinBox->blockSignals(true);
        QMessageBox::warning(this,"Error","Number of Transactions can't be more than 2");
         ui->DevD_spinBox->blockSignals(false);
    }
}



void MainWindow::on_DevA_ByteIndex_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Byte 1"){
         ui->DevA_Byte1->setEnabled(true);
         ui->DevA_Byte2->setEnabled(false);
         ui->DevA_Byte3->setEnabled(false);
         ui->DevA_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 2"){
        ui->DevA_Byte1->setEnabled(false);
        ui->DevA_Byte2->setEnabled(true);
        ui->DevA_Byte3->setEnabled(false);
        ui->DevA_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 3"){
        ui->DevA_Byte1->setEnabled(false);
        ui->DevA_Byte2->setEnabled(false);
        ui->DevA_Byte3->setEnabled(true);
        ui->DevA_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 4")
    {
        ui->DevA_Byte1->setEnabled(false);
        ui->DevA_Byte2->setEnabled(false);
        ui->DevA_Byte3->setEnabled(false);
        ui->DevA_Byte4->setEnabled(true);
    }
    else {
        ui->DevA_Byte1->setEnabled(true);
        ui->DevA_Byte2->setEnabled(true);
        ui->DevA_Byte3->setEnabled(true);
        ui->DevA_Byte4->setEnabled(true);
    }
}

void MainWindow::on_DevB_ByteIndex_currentTextChanged(const QString &arg1)
{

    if(arg1 == "Byte 1"){
         ui->DevB_Byte1->setEnabled(true);
         ui->DevB_Byte2->setEnabled(false);
         ui->DevB_Byte3->setEnabled(false);
         ui->DevB_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 2"){
        ui->DevB_Byte1->setEnabled(false);
        ui->DevB_Byte2->setEnabled(true);
        ui->DevB_Byte3->setEnabled(false);
        ui->DevB_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 3"){
        ui->DevB_Byte1->setEnabled(false);
        ui->DevB_Byte2->setEnabled(false);
        ui->DevB_Byte3->setEnabled(true);
        ui->DevB_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 4")
    {
        ui->DevB_Byte1->setEnabled(false);
        ui->DevB_Byte2->setEnabled(false);
        ui->DevB_Byte3->setEnabled(false);
        ui->DevB_Byte4->setEnabled(true);
    }
    else {
        ui->DevB_Byte1->setEnabled(true);
        ui->DevB_Byte2->setEnabled(true);
        ui->DevB_Byte3->setEnabled(true);
        ui->DevB_Byte4->setEnabled(true);
    }
}

void MainWindow::on_DevC_ByteIndex_currentTextChanged(const QString &arg1)
{

    if(arg1 == "Byte 1"){
         ui->DevC_Byte1->setEnabled(true);
         ui->DevC_Byte2->setEnabled(false);
         ui->DevC_Byte3->setEnabled(false);
         ui->DevC_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 2"){
        ui->DevC_Byte1->setEnabled(false);
        ui->DevC_Byte2->setEnabled(true);
        ui->DevC_Byte3->setEnabled(false);
        ui->DevC_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 3"){
        ui->DevC_Byte1->setEnabled(false);
        ui->DevC_Byte2->setEnabled(false);
        ui->DevC_Byte3->setEnabled(true);
        ui->DevC_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 4")
    {
        ui->DevC_Byte1->setEnabled(false);
        ui->DevC_Byte2->setEnabled(false);
        ui->DevC_Byte3->setEnabled(false);
        ui->DevC_Byte4->setEnabled(true);
    }
    else {
        ui->DevC_Byte1->setEnabled(true);
        ui->DevC_Byte2->setEnabled(true);
        ui->DevC_Byte3->setEnabled(true);
        ui->DevC_Byte4->setEnabled(true);
    }
}

void MainWindow::on_DevD_ByteIndex_currentTextChanged(const QString &arg1)
{

    if(arg1 == "Byte 1"){
         ui->DevD_Byte1->setEnabled(true);
         ui->DevD_Byte2->setEnabled(false);
         ui->DevD_Byte3->setEnabled(false);
         ui->DevD_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 2"){
        ui->DevD_Byte1->setEnabled(false);
        ui->DevD_Byte2->setEnabled(true);
        ui->DevD_Byte3->setEnabled(false);
        ui->DevD_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 3"){
        ui->DevD_Byte1->setEnabled(false);
        ui->DevD_Byte2->setEnabled(false);
        ui->DevD_Byte3->setEnabled(true);
        ui->DevD_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 4")
    {
        ui->DevD_Byte1->setEnabled(false);
        ui->DevD_Byte2->setEnabled(false);
        ui->DevD_Byte3->setEnabled(false);
        ui->DevD_Byte4->setEnabled(true);
    }
    else {
        ui->DevD_Byte1->setEnabled(true);
        ui->DevD_Byte2->setEnabled(true);
        ui->DevD_Byte3->setEnabled(true);
        ui->DevD_Byte4->setEnabled(true);
    }
}

void MainWindow::on_Submit_clicked(bool checked)
{

    delay.append(ui->Delay->value());


    if(ui->DevA_InitiatorRadio->isChecked())
        MastersSelect.append(DeviceA);
    if(ui->DevB_InitiatorRadio->isChecked())
        MastersSelect.append(DeviceB);
    if(ui->DevC_InitiatorRadio->isChecked())
        MastersSelect.append(DeviceC);
    if(ui->DevD_InitiatorRadio->isChecked())
        MastersSelect.append(DeviceD);




    for(int i=0;i<10;i++){
        if(i == ui->DevA_RowIndex->currentIndex()){

            if(ui->DevA_ByteIndex->currentIndex() ==1)
                DeviceA->SetMemoryByte(ui->DevA_Byte1->text(),i,0);
            else if(ui->DevA_ByteIndex->currentIndex() == 2)
                DeviceA->SetMemoryByte(ui->DevA_Byte2->text(),i,1);
            else if(ui->DevA_ByteIndex->currentIndex() == 3)
                DeviceA->SetMemoryByte(ui->DevA_Byte3->text(),i,2);
            else if(ui->DevA_ByteIndex->currentIndex() == 4)
                DeviceA->SetMemoryByte(ui->DevA_Byte4->text(),i,3);

        }
        if(i == ui->DevB_RowIndex->currentIndex()){

            if(ui->DevB_ByteIndex->currentIndex() ==1)
                DeviceB->SetMemoryByte(ui->DevB_Byte1->text(),i,0);
            else if(ui->DevB_ByteIndex->currentIndex() == 2)
                DeviceB->SetMemoryByte(ui->DevB_Byte2->text(),i,1);
            else if(ui->DevB_ByteIndex->currentIndex() == 3)
                DeviceB->SetMemoryByte(ui->DevB_Byte3->text(),i,2);
            else if(ui->DevB_ByteIndex->currentIndex() == 4)
                DeviceB->SetMemoryByte(ui->DevB_Byte4->text(),i,3);
        }
        if(i == ui->DevC_RowIndex->currentIndex()){
            if(ui->DevC_ByteIndex->currentIndex() ==1)
                DeviceC->SetMemoryByte(ui->DevC_Byte1->text(),i,0);
            else if(ui->DevC_ByteIndex->currentIndex() == 2)
                DeviceC->SetMemoryByte(ui->DevC_Byte2->text(),i,1);
            else if(ui->DevC_ByteIndex->currentIndex() == 3)
                DeviceC->SetMemoryByte(ui->DevC_Byte3->text(),i,2);
            else if(ui->DevC_ByteIndex->currentIndex() == 4)
                DeviceC->SetMemoryByte(ui->DevC_Byte4->text(),i,3);
        }
        if(i == ui->DevD_RowIndex->currentIndex()){
            if(ui->DevD_ByteIndex->currentIndex() ==1)
                DeviceD->SetMemoryByte(ui->DevD_Byte1->text(),i,0);
            else if(ui->DevD_ByteIndex->currentIndex() == 2)
                DeviceD->SetMemoryByte(ui->DevD_Byte2->text(),i,1);
            else if(ui->DevD_ByteIndex->currentIndex() == 3)
                DeviceD->SetMemoryByte(ui->DevD_Byte3->text(),i,2);
            else if(ui->DevD_ByteIndex->currentIndex() == 4)
                DeviceD->SetMemoryByte(ui->DevD_Byte4->text(),i,3);
        }
    }

}


void MainWindow::on_DevA_RowIndex_currentIndexChanged(const QString &arg1)
{
    for(int i=0;i<10;i++){
        if(i == ui->DevA_RowIndex->currentIndex()){

            ui->DevA_Byte1->setText(DeviceA->GetMemoryByte(i,0));
            ui->DevA_Byte2->setText(DeviceA->GetMemoryByte(i,1));
            ui->DevA_Byte3->setText(DeviceA->GetMemoryByte(i,2));
            ui->DevA_Byte4->setText(DeviceA->GetMemoryByte(i,3));

        }
    }
}

void MainWindow::on_DevB_RowIndex_currentIndexChanged(const QString &arg1)
{
    for(int i=0;i<10;i++){
        if(i == ui->DevB_RowIndex->currentIndex()){

            ui->DevB_Byte1->setText(DeviceB->GetMemoryByte(i,0));
            ui->DevB_Byte2->setText(DeviceB->GetMemoryByte(i,1));
            ui->DevB_Byte3->setText(DeviceB->GetMemoryByte(i,2));
            ui->DevB_Byte4->setText(DeviceB->GetMemoryByte(i,3));

        }
    }
}

void MainWindow::on_DevC_RowIndex_currentIndexChanged(const QString &arg1)
{
    for(int i=0;i<10;i++){
        if(i == ui->DevC_RowIndex->currentIndex()){

            ui->DevC_Byte1->setText(DeviceC->GetMemoryByte(i,0));
            ui->DevC_Byte2->setText(DeviceC->GetMemoryByte(i,1));
            ui->DevC_Byte3->setText(DeviceC->GetMemoryByte(i,2));
            ui->DevC_Byte4->setText(DeviceC->GetMemoryByte(i,3));

        }
    }
}

void MainWindow::on_DevD_RowIndex_currentIndexChanged(const QString &arg1)
{
    for(int i=0;i<10;i++){
        if(i == ui->DevD_RowIndex->currentIndex()){

            ui->DevD_Byte1->setText(DeviceD->GetMemoryByte(i,0));
            ui->DevD_Byte2->setText(DeviceD->GetMemoryByte(i,1));
            ui->DevD_Byte3->setText(DeviceD->GetMemoryByte(i,2));
            ui->DevD_Byte4->setText(DeviceD->GetMemoryByte(i,3));

        }
    }
}
