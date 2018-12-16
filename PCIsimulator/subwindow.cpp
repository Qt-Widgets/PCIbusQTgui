#include "subwindow.h"
#include "ui_subwindow.h"
#include"mainwindow.h"
#include <QDebug>
#include <QPushButton>

subWindow::subWindow(QWidget *parent,int num_Trans) :
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
        for(int i =0 ; i<ui->verticalLayout_7->count();i++)
        {
            QWidget *widget = ui->verticalLayout_7->itemAt(i)->widget();

            if (widget != NULL)
              {
                widget->hide();
              }
        }
    }
}

subWindow::~subWindow()
{
    delete ui;
}

void subWindow::ComboBoxItems(){

}

void subWindow::on_Trans1_Spinbox_editingFinished()
{
    for(int i=1 ; i<=ui->Trans1_Spinbox->value();i++)
    {
       ui->Trans1_comboBox->addItem("Data Phase" + QString::number(i));
    }
}

void subWindow::on_Trans2_Spinbox_editingFinished()
{
    for(int i=1 ; i<=ui->Trans2_Spinbox->value();i++)
    {
       ui->Trans2_comboBox->addItem("Data Phase" + QString::number(i));
    }
}

void subWindow::on_Trans3_Spinbox_editingFinished()
{
    for(int i=1 ; i<=ui->Trans3_Spinbox->value();i++)
    {
       ui->Trans3_comboBox->addItem("Data Phase" + QString::number(i));
    }
}

void subWindow::on_Trans4_Spinbox_editingFinished()
{
    for(int i=1 ; i<=ui->Trans4_Spinbox->value();i++)
    {
       ui->Trans4_comboBox->addItem("Data Phase" + QString::number(i));
    }
}
