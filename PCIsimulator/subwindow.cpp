#include "subwindow.h"
#include "ui_subwindow.h"
#include"mainwindow.h"
#include <QDebug>
#include <QPushButton>
#include<QMessageBox>
#include"device_signals.h"

QVector <int> confirm_checks = {0,0};
int numberOfTrans;
subWindow::subWindow(QWidget *parent,int num_Trans, QString Dev_name,
                     Device_Signals *devA_main,Device_Signals *devB_main,Device_Signals *devC_main,Device_Signals *devD_main,
                     DEVICE *A,DEVICE *B, DEVICE *C,DEVICE *D) :
    QDialog(parent),
    ui(new Ui::subWindow)
{
    ui->setupUi(this);

    DeviceA = A;
    DeviceB = B;
    DeviceC = C;
    DeviceD = D;


    devA_sub= devA_main;
    devB_sub= devB_main;
    devC_sub= devC_main;
    devD_sub= devD_main;

    numberOfTrans = num_Trans;


    if(num_Trans < 4)
    {
        for(int i =0 ; i<ui->verticalLayout_7->count();i++)
        {
            QWidget *widget = ui->verticalLayout_7->itemAt(i)->widget();

            if (widget != NULL)
              {
                widget->hide();
              }
        }


    }

    if (num_Trans <3)
    {
        for(int i =0 ; i<ui->verticalLayout_6->count();i++)
        {
            QWidget *widget = ui->verticalLayout_6->itemAt(i)->widget();

            if (widget != NULL)
              {
                widget->hide();
              }
        }


    }
    if (num_Trans < 2)
    {
        for(int i =0 ; i<ui->verticalLayout_5->count();i++)
        {
            QWidget *widget = ui->verticalLayout_5->itemAt(i)->widget();

            if (widget != NULL)
              {
                widget->hide();
              }
        }

    }

    if(num_Trans >0){

        if(Dev_name == "DEVICE A"){
            ui->Trans1_Target->addItem("Select Target");
            ui->Trans1_Target->addItem("DEVICE B");
            ui->Trans1_Target->addItem("DEVICE C");
            ui->Trans1_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE B"){
            ui->Trans1_Target->addItem("Select Target");
            ui->Trans1_Target->addItem("DEVICE A");
            ui->Trans1_Target->addItem("DEVICE C");
            ui->Trans1_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE C"){
            ui->Trans1_Target->addItem("Select Target");
            ui->Trans1_Target->addItem("DEVICE A");
            ui->Trans1_Target->addItem("DEVICE D");
            ui->Trans1_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE D"){
            ui->Trans1_Target->addItem("Select Target");
            ui->Trans1_Target->addItem("DEVICE A");
            ui->Trans1_Target->addItem("DEVICE B");
            ui->Trans1_Target->addItem("DEVICE C");
        }
    }

    if(num_Trans>1){
        if(Dev_name == "DEVICE A"){
            ui->Trans2_Target->addItem("Select Target");
            ui->Trans2_Target->addItem("DEVICE B");
            ui->Trans2_Target->addItem("DEVICE C");
            ui->Trans2_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE B"){
            ui->Trans2_Target->addItem("Select Target");
            ui->Trans2_Target->addItem("DEVICE A");
            ui->Trans2_Target->addItem("DEVICE C");
            ui->Trans2_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE C"){
            ui->Trans2_Target->addItem("Select Target");
            ui->Trans2_Target->addItem("DEVICE A");
            ui->Trans2_Target->addItem("DEVICE D");
            ui->Trans2_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE D"){
            ui->Trans2_Target->addItem("Select Target");
            ui->Trans2_Target->addItem("DEVICE A");
            ui->Trans2_Target->addItem("DEVICE B");
            ui->Trans2_Target->addItem("DEVICE C");
        }

    }

    if(num_Trans > 2){

        if(Dev_name == "DEVICE A"){
            ui->Trans3_Target->addItem("Select Target");
            ui->Trans3_Target->addItem("DEVICE B");
            ui->Trans3_Target->addItem("DEVICE C");
            ui->Trans3_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE B"){
            ui->Trans3_Target->addItem("Select Target");
            ui->Trans3_Target->addItem("DEVICE A");
            ui->Trans3_Target->addItem("DEVICE C");
            ui->Trans3_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE C"){
            ui->Trans3_Target->addItem("Select Target");
            ui->Trans3_Target->addItem("DEVICE A");
            ui->Trans3_Target->addItem("DEVICE D");
            ui->Trans3_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE D"){
            ui->Trans3_Target->addItem("Select Target");
            ui->Trans3_Target->addItem("DEVICE A");
            ui->Trans3_Target->addItem("DEVICE B");
            ui->Trans3_Target->addItem("DEVICE C");
        }
    }

    if(num_Trans>3){
        if(Dev_name == "DEVICE A"){
            ui->Trans4_Target->addItem("Select Target");
            ui->Trans4_Target->addItem("DEVICE B");
            ui->Trans4_Target->addItem("DEVICE C");
            ui->Trans4_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE B"){
            ui->Trans4_Target->addItem("Select Target");
            ui->Trans4_Target->addItem("DEVICE A");
            ui->Trans4_Target->addItem("DEVICE C");
            ui->Trans4_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE C"){
            ui->Trans4_Target->addItem("Select Target");
            ui->Trans4_Target->addItem("DEVICE A");
            ui->Trans4_Target->addItem("DEVICE D");
            ui->Trans4_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE D"){
            ui->Trans4_Target->addItem("Select Target");
            ui->Trans4_Target->addItem("DEVICE A");
            ui->Trans4_Target->addItem("DEVICE B");
            ui->Trans4_Target->addItem("DEVICE C");
        }
    }

}

subWindow::~subWindow()
{
    delete ui;
}


void subWindow::on_Trans1_comboBox_currentIndexChanged(const QString &arg1)
{
       ui->Trans1_Byte1->setChecked(false);
       ui->Trans1_Byte2->setChecked(false);
       ui->Trans1_Byte3->setChecked(false);
       ui->Trans1_Byte4->setChecked(false);
}

void subWindow::on_Trans2_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->Trans2_Byte1->setChecked(false);
    ui->Trans2_Byte2->setChecked(false);
    ui->Trans2_Byte3->setChecked(false);
    ui->Trans2_Byte4->setChecked(false);
}

void subWindow::on_Trans1_Spinbox_editingFinished()
{
    if(ui->Trans1_Spinbox->value()<=3){
        ui->Trans1_Spinbox->blockSignals(true);
        ui->Trans1_comboBox->clear();

        for(int i=1 ; i<=ui->Trans1_Spinbox->value();i++)
        {
           ui->Trans1_comboBox->addItem("Data Phase" + QString::number(i));
        }

        confirm_checks[0] = ui->Trans1_Spinbox->value();

        ui->Trans1_Spinbox->blockSignals(false);

        if(subWindow::windowTitle() == "DEVICE A"){
            devA_sub->set_numOfPhases(0,ui->Trans1_Spinbox->value());
         }

         if(subWindow::windowTitle() == "DEVICE B"){
            devB_sub->set_numOfPhases(0,ui->Trans1_Spinbox->value());
         }
         if(subWindow::windowTitle() == "DEVICE C"){
            devC_sub->set_numOfPhases(0,ui->Trans1_Spinbox->value());
         }
         if(subWindow::windowTitle() == "DEVICE D"){
            devD_sub->set_numOfPhases(0,ui->Trans1_Spinbox->value());
         }
    }
    else{
        ui->Trans1_Spinbox->blockSignals(true);
        QMessageBox::warning(this,"Error","Number of Data Phases can't be more than 3");
        ui->Trans1_Spinbox->blockSignals(false);
    }
}

void subWindow::on_Trans2_Spinbox_editingFinished()
{
    if(ui->Trans2_Spinbox->value()<=3){
        ui->Trans2_Spinbox->blockSignals(true);
        ui->Trans2_comboBox->clear();

        for(int i=1 ; i<=ui->Trans2_Spinbox->value();i++)
        {
           ui->Trans2_comboBox->addItem("Data Phase" + QString::number(i));
        }

        confirm_checks[1] = ui->Trans2_Spinbox->value();
        ui->Trans2_Spinbox->blockSignals(false);

        if(subWindow::windowTitle() == "DEVICE A"){
            devA_sub->set_numOfPhases(1,ui->Trans2_Spinbox->value());
         }

         if(subWindow::windowTitle() == "DEVICE B"){
            devB_sub->set_numOfPhases(1,ui->Trans2_Spinbox->value());
         }
         if(subWindow::windowTitle() == "DEVICE C"){
            devC_sub->set_numOfPhases(1,ui->Trans2_Spinbox->value());
         }
         if(subWindow::windowTitle() == "DEVICE D"){
            devD_sub->set_numOfPhases(1,ui->Trans2_Spinbox->value());
         }
    }
    else{
        ui->Trans2_Spinbox->blockSignals(true);
        QMessageBox::warning(this,"Error","Number of Data Phases can't be more than 3");
        ui->Trans2_Spinbox->blockSignals(false);
    }
}




void subWindow::on_Trans1_Target_currentTextChanged(const QString &arg1)
{
    if(subWindow::windowTitle() == "DEVICE A"){
        if(arg1=="DEVICE B"){
            devA_sub->set_targetSelect(DeviceB,0);
        }
        else if (arg1 == "DEVICE C"){
            devA_sub->set_targetSelect(DeviceC,0);
        }
        else if(arg1 == "DEVICE D"){
            devA_sub->set_targetSelect(DeviceC,0);

        }
    }
    if(subWindow::windowTitle() == "DEVICE B"){
        if(arg1=="DEVICE A"){
            devB_sub->set_targetSelect(DeviceA,0);
        }
        else if (arg1 == "DEVICE C"){
            devB_sub->set_targetSelect(DeviceC,0);
        }
        else if(arg1 == "DEVICE D"){
            devB_sub->set_targetSelect(DeviceD,0);
        }
    }
    if(subWindow::windowTitle() == "DEVICE C"){
        if(arg1=="DEVICE A"){
            devC_sub->set_targetSelect(DeviceA,0);
        }
        else if (arg1 == "DEVICE B"){
            devC_sub->set_targetSelect(DeviceB,0);
        }
        else if(arg1 == "DEVICE D"){
            devC_sub->set_targetSelect(DeviceD,0);
        }
    }
    if(subWindow::windowTitle() == "DEVICE D"){
        if(arg1=="DEVICE A"){
            devD_sub->set_targetSelect(DeviceA,0);
        }
        else if (arg1 == "DEVICE B"){
            devD_sub->set_targetSelect(DeviceB,0);
        }
        else if(arg1 == "DEVICE D"){
            devD_sub->set_targetSelect(DeviceC,0);

        }
    }
}

void subWindow::on_Trans2_Target_currentTextChanged(const QString &arg1)
{
    if(subWindow::windowTitle() == "DEVICE A"){
        if(arg1=="DEVICE B"){
            devA_sub->set_targetSelect(DeviceB,1);

        }
        else if (arg1 == "DEVICE C"){
             devA_sub->set_targetSelect(DeviceC,1);
        }
        else if(arg1 == "DEVICE D"){
            devA_sub->set_targetSelect(DeviceC,1);
        }
    }
    if(subWindow::windowTitle() == "DEVICE B"){
        if(arg1=="DEVICE A"){
            devB_sub->set_targetSelect(DeviceA,1);
        }
        else if (arg1 == "DEVICE C"){
            devB_sub->set_targetSelect(DeviceC,1);
        }
        else if(arg1 == "DEVICE D"){
            devB_sub->set_targetSelect(DeviceC,1);
        }
    }
    if(subWindow::windowTitle() == "DEVICE C"){
        if(arg1=="DEVICE A"){
            devC_sub->set_targetSelect(DeviceA,1);
        }
        else if (arg1 == "DEVICE B"){
             devC_sub->set_targetSelect(DeviceB,1);
        }
        else if(arg1 == "DEVICE D"){
            devC_sub->set_targetSelect(DeviceD,1);
        }
    }
    if(subWindow::windowTitle() == "DEVICE D"){
        if(arg1=="DEVICE A"){
            devD_sub->set_targetSelect(DeviceA,1);
        }
        else if (arg1 == "DEVICE B"){
             devD_sub->set_targetSelect(DeviceB,1);
        }
        else if(arg1 == "DEVICE D"){
             devD_sub->set_targetSelect(DeviceC,1);
        }
    }
}



void subWindow::on_Trans1_ReadRadio_clicked(bool checked)
{
     if(subWindow::windowTitle() == "DEVICE A"){
        devA_sub->set_controlSelect("Read",0);
     }

     if(subWindow::windowTitle() == "DEVICE B"){
        devB_sub->set_controlSelect("Read",0);
     }
     if(subWindow::windowTitle() == "DEVICE C"){
        devC_sub->set_controlSelect("Read",0);
     }
     if(subWindow::windowTitle() == "DEVICE D"){
        devD_sub->set_controlSelect("Read",0);
     }
}

void subWindow::on_Trans2_ReadRadio_clicked(bool checked)
{
    if(subWindow::windowTitle() == "DEVICE A"){
       devA_sub->set_controlSelect("Read",1);
    }

    if(subWindow::windowTitle() == "DEVICE B"){
       devB_sub->set_controlSelect("Read",1);
    }
    if(subWindow::windowTitle() == "DEVICE C"){
       devC_sub->set_controlSelect("Read",1);
    }
    if(subWindow::windowTitle() == "DEVICE D"){
       devD_sub->set_controlSelect("Read",1);
    }
}



void subWindow::on_Trans1_WriteRadio_clicked(bool checked)
{
    if(subWindow::windowTitle() == "DEVICE A"){
       devA_sub->set_controlSelect("Write",0);
    }

    if(subWindow::windowTitle() == "DEVICE B"){
       devB_sub->set_controlSelect("Write",0);
    }
    if(subWindow::windowTitle() == "DEVICE C"){
       devC_sub->set_controlSelect("Write",0);
    }
    if(subWindow::windowTitle() == "DEVICE D"){
       devD_sub->set_controlSelect("Write",0);
    }
}

void subWindow::on_Trans2_WriteRadio_clicked(bool checked)
{
    if(subWindow::windowTitle() == "DEVICE A"){
       devA_sub->set_controlSelect("Write",1);
    }

    if(subWindow::windowTitle() == "DEVICE B"){
       devB_sub->set_controlSelect("Write",1);
    }
    if(subWindow::windowTitle() == "DEVICE C"){
       devC_sub->set_controlSelect("Write",1);
    }
    if(subWindow::windowTitle() == "DEVICE D"){
       devD_sub->set_controlSelect("Write",1);
    }
}



void subWindow::on_Trans1_pushButton_clicked()
{
    confirm_checks[0]--;

    QString word = "";

    if(subWindow::windowTitle() == "DEVICE A"){
        for(int i=0 ; i<ui->Trans1_Spinbox->value();i++){

            if( ui->Trans1_comboBox->currentIndex() == i){
                if(ui->Trans1_Byte1->isChecked())
                    word +='1';
                    //devA_sub->set_ByteEnable(0,i,'1');
                if(ui->Trans1_Byte2->isChecked())
                    word +='2';

                if(ui->Trans1_Byte3->isChecked())
                    word +='3';

                if(ui->Trans1_Byte4->isChecked())
                    word +='4';

                devA_sub->set_ByteEnable(0,i,word);

            }
        }

    }

    if(subWindow::windowTitle() == "DEVICE B"){

        for(int i=0 ; i<ui->Trans1_Spinbox->value();i++){

            if( ui->Trans1_comboBox->currentIndex() == i){
                if(ui->Trans1_Byte1->isChecked())
                    word +='1';
                    //devB_sub->set_ByteEnable(0,i,'1');
                if(ui->Trans1_Byte2->isChecked())
                    word +='2';
                if(ui->Trans1_Byte3->isChecked())
                    word +='3';
                if(ui->Trans1_Byte4->isChecked())
                    word +='4';

                devB_sub->set_ByteEnable(0,i,word);
            }
        }

    }
    if(subWindow::windowTitle() == "DEVICE C"){

        for(int i=0 ; i<ui->Trans1_Spinbox->value();i++){

            if( ui->Trans1_comboBox->currentIndex() == i){
                if(ui->Trans1_Byte1->isChecked())
                    word +='1';
                    //devC_sub->set_ByteEnable(0,i,'1');
                if(ui->Trans1_Byte2->isChecked())
                    word +='2';
                if(ui->Trans1_Byte3->isChecked())
                    word +='3';
                if(ui->Trans1_Byte4->isChecked())
                    word +='4';

                devC_sub->set_ByteEnable(0,i,word);
            }
        }

    }
    if(subWindow::windowTitle() == "DEVICE D"){

        for(int i=0 ; i<ui->Trans1_Spinbox->value();i++){

            if( ui->Trans1_comboBox->currentIndex() == i){
                if(ui->Trans1_Byte1->isChecked())
                    //devD_sub->set_ByteEnable(0,i,'1');
                    word +='1';
                if(ui->Trans1_Byte2->isChecked())
                    word +='2';
                if(ui->Trans1_Byte3->isChecked())
                    word +='3';
                if(ui->Trans1_Byte4->isChecked())
                    word +='4';

                devD_sub->set_ByteEnable(0,i,word);
            }
        }

    }

    QMessageBox::information(this,"Info","Byte Enable for this Data Phase stored Successfully");
}

void subWindow::on_Trans2_pushButton_clicked(bool checked)
{
    confirm_checks[1]--;

    QString word = "";

    if(subWindow::windowTitle() == "DEVICE A"){
        for(int i=0 ; i<ui->Trans2_Spinbox->value();i++){

            if( ui->Trans2_comboBox->currentIndex() == i){
                if(ui->Trans2_Byte1->isChecked())
                    //devA_sub->set_ByteEnable(1,i,'1');
                    word +='1';
                if(ui->Trans2_Byte2->isChecked())
                    word +='2';
                if(ui->Trans2_Byte3->isChecked())
                    word +='3';
                if(ui->Trans2_Byte4->isChecked())
                    word +='4';

                devA_sub->set_ByteEnable(1,i,word);
            }
        }

    }

    if(subWindow::windowTitle() == "DEVICE B"){

        for(int i=0 ; i<ui->Trans2_Spinbox->value();i++){

            if( ui->Trans2_comboBox->currentIndex() == i){
                if(ui->Trans2_Byte1->isChecked())
                    //devB_sub->set_ByteEnable(1,i,'1');
                    word +='1';
                if(ui->Trans2_Byte2->isChecked())
                    word +='2';
                if(ui->Trans2_Byte3->isChecked())
                    word +='3';
                if(ui->Trans2_Byte4->isChecked())
                    word +='4';

                devB_sub->set_ByteEnable(1,i,word);
            }
        }

    }
    if(subWindow::windowTitle() == "DEVICE C"){

        for(int i=0 ; i<ui->Trans2_Spinbox->value();i++){

            if( ui->Trans2_comboBox->currentIndex() == i){
                if(ui->Trans2_Byte1->isChecked())
                   // devC_sub->set_ByteEnable(1,i,'1');
                    word +='1';
                if(ui->Trans2_Byte2->isChecked())
                    word +='2';
                if(ui->Trans2_Byte3->isChecked())
                    word +='3';
                if(ui->Trans2_Byte4->isChecked())
                    word +='4';

                devC_sub->set_ByteEnable(1,i,word);
            }
        }

    }
    if(subWindow::windowTitle() == "DEVICE D"){

        for(int i=0 ; i<ui->Trans2_Spinbox->value();i++){

            if( ui->Trans2_comboBox->currentIndex() == i){
                if(ui->Trans2_Byte1->isChecked())
                    //devD_sub->set_ByteEnable(1,i,'1');
                    word += '1';
                if(ui->Trans2_Byte2->isChecked())
                    word += '2';
                if(ui->Trans2_Byte3->isChecked())
                    word += '3';
                if(ui->Trans2_Byte4->isChecked())
                    word += '4';

                devD_sub->set_ByteEnable(1,i,word);
            }
        }

    }
    QMessageBox::information(this,"Info","Byte Enable for this Data Phase stored Successfully");
}








void subWindow::on_Apply_button_clicked()
{
    int error=0;

    if(ui->Trans1_Target->currentText() == "Select Target"){
        QMessageBox::warning(this,"Error","You forgot to select target of first transaction");
        error=1;
    }

    if(!(ui->Trans1_ReadRadio->isChecked()) && !(ui->Trans1_WriteRadio->isChecked()) ){
        QMessageBox::warning(this,"Error","You forgot to select control of first transaction");
        error=1;
    }
    if(ui->Trans1_Spinbox->value() == 0){
        QMessageBox::warning(this,"Error","You forgot to enter number of data phases of first transaction");
        error=1;
    }
    if(confirm_checks[0]>0){
        QMessageBox::warning(this,"Error","You forgot to enter byte enable of a data phase");
        error=1;
    }
    if(numberOfTrans==2){
        if(ui->Trans2_Target->currentText() == "Select Target"){
            QMessageBox::warning(this,"Error","You forgot to select target of Second transaction");
            error=1;
        }

        if(!(ui->Trans2_ReadRadio->isChecked()) && !(ui->Trans2_WriteRadio->isChecked()) ){
            QMessageBox::warning(this,"Error","You forgot to select control of Second transaction");
            error=1;
        }
        if(ui->Trans2_Spinbox->value() == 0){
            QMessageBox::warning(this,"Error","You forgot to enter number of data phases of Second transaction");
            error=1;
        }
        if(confirm_checks[1]>0){
            QMessageBox::warning(this,"Error","You forgot to enter byte enable of a data phase");
            error=1;
        }
    }

    if(error==0)
        this->close();
}


