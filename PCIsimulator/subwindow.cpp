#include "subwindow.h"
#include "ui_subwindow.h"
#include"mainwindow.h"
#include <QDebug>
#include <QPushButton>
#include"device_signals.h"
subWindow::subWindow(QWidget *parent,int num_Trans, QString Dev_name) :
    QDialog(parent),
    ui(new Ui::subWindow)
{
    ui->setupUi(this);


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
            ui->Trans1_Target->addItem("DEVICE B");
            ui->Trans1_Target->addItem("DEVICE C");
            ui->Trans1_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE B"){
            ui->Trans1_Target->addItem("DEVICE A");
            ui->Trans1_Target->addItem("DEVICE C");
            ui->Trans1_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE C"){
            ui->Trans1_Target->addItem("DEVICE A");
            ui->Trans1_Target->addItem("DEVICE D");
            ui->Trans1_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE D"){
            ui->Trans1_Target->addItem("DEVICE A");
            ui->Trans1_Target->addItem("DEVICE B");
            ui->Trans1_Target->addItem("DEVICE C");
        }
    }

    if(num_Trans>1){
        if(Dev_name == "DEVICE A"){
            ui->Trans2_Target->addItem("DEVICE B");
            ui->Trans2_Target->addItem("DEVICE C");
            ui->Trans2_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE B"){
            ui->Trans2_Target->addItem("DEVICE A");
            ui->Trans2_Target->addItem("DEVICE C");
            ui->Trans2_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE C"){
            ui->Trans2_Target->addItem("DEVICE A");
            ui->Trans2_Target->addItem("DEVICE D");
            ui->Trans2_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE D"){
            ui->Trans2_Target->addItem("DEVICE A");
            ui->Trans2_Target->addItem("DEVICE B");
            ui->Trans2_Target->addItem("DEVICE C");
        }

    }

    if(num_Trans > 2){

        if(Dev_name == "DEVICE A"){
            ui->Trans3_Target->addItem("DEVICE B");
            ui->Trans3_Target->addItem("DEVICE C");
            ui->Trans3_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE B"){
            ui->Trans3_Target->addItem("DEVICE A");
            ui->Trans3_Target->addItem("DEVICE C");
            ui->Trans3_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE C"){
            ui->Trans3_Target->addItem("DEVICE A");
            ui->Trans3_Target->addItem("DEVICE D");
            ui->Trans3_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE D"){
            ui->Trans3_Target->addItem("DEVICE A");
            ui->Trans3_Target->addItem("DEVICE B");
            ui->Trans3_Target->addItem("DEVICE C");
        }
    }

    if(num_Trans>3){
        if(Dev_name == "DEVICE A"){
            ui->Trans4_Target->addItem("DEVICE B");
            ui->Trans4_Target->addItem("DEVICE C");
            ui->Trans4_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE B"){
            ui->Trans4_Target->addItem("DEVICE A");
            ui->Trans4_Target->addItem("DEVICE C");
            ui->Trans4_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE C"){
            ui->Trans4_Target->addItem("DEVICE A");
            ui->Trans4_Target->addItem("DEVICE D");
            ui->Trans4_Target->addItem("DEVICE D");
        }
        else if (Dev_name == "DEVICE D"){
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



void subWindow::on_Trans1_Spinbox_editingFinished()
{
    ui->Trans1_Spinbox->blockSignals(true);
    for(int i=1 ; i<=ui->Trans1_Spinbox->value();i++)
    {
       ui->Trans1_comboBox->addItem("Data Phase" + QString::number(i));
    }
    ui->Trans1_Spinbox->setEnabled(false);
    ui->Trans1_Spinbox->blockSignals(false);
}

void subWindow::on_Trans2_Spinbox_editingFinished()
{
    ui->Trans2_Spinbox->blockSignals(true);
    for(int i=1 ; i<=ui->Trans2_Spinbox->value();i++)
    {
       ui->Trans2_comboBox->addItem("Data Phase" + QString::number(i));
    }
    ui->Trans2_Spinbox->setEnabled(false);
    ui->Trans2_Spinbox->blockSignals(false);
}

void subWindow::on_Trans3_Spinbox_editingFinished()
{
    ui->Trans3_Spinbox->blockSignals(true);
    for(int i=1 ; i<=ui->Trans3_Spinbox->value();i++)
    {
       ui->Trans3_comboBox->addItem("Data Phase" + QString::number(i));
    }
    ui->Trans3_Spinbox->setEnabled(false);
    ui->Trans3_Spinbox->blockSignals(false);
}

void subWindow::on_Trans4_Spinbox_editingFinished()
{
    ui->Trans4_Spinbox->blockSignals(true);
    for(int i=1 ; i<=ui->Trans4_Spinbox->value();i++)
    {
       ui->Trans4_comboBox->addItem("Data Phase" + QString::number(i));
    }
    ui->Trans4_Spinbox->setEnabled(false);
    ui->Trans4_Spinbox->blockSignals(false);
}

void subWindow::on_Trans1_comboBox_currentIndexChanged(const QString &arg1)
{
       ui->Trans1_Byte1->setChecked(false);
       ui->Trans1_Byte2->setChecked(false);
       ui->Trans1_Byte3->setChecked(false);
       ui->Trans1_Byte4->setChecked(false);
}




void subWindow::on_Trans1_Target_currentTextChanged(const QString &arg1)
{
    DevA.set_targetSelect(arg1);
}
