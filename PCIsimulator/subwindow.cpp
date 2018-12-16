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

    if(num_Trans==0)
    {
        for(int i =0 ; i<ui->verticalLayout_4->count();i++){
            QWidget *widget = ui->verticalLayout_4->itemAt(i)->widget();

            if (widget != NULL)
              {
                widget->hide();
              }
        }
        for(int i =0 ; i<ui->verticalLayout_5->count();i++){
            QWidget *widget = ui->verticalLayout_5->itemAt(i)->widget();

            if (widget != NULL)
              {
                widget->hide();
              }
        }
        for(int i =0 ; i<ui->verticalLayout_6->count();i++){
            QWidget *widget = ui->verticalLayout_6->itemAt(i)->widget();

            if (widget != NULL)
              {
                widget->hide();
              }
        }
        for(int i =0 ; i<ui->verticalLayout_7->count();i++){
            QWidget *widget = ui->verticalLayout_7->itemAt(i)->widget();

            if (widget != NULL)
              {
                widget->hide();
              }

        }

    }
    else if (num_Trans == 1){
        for(int i =0 ; i<ui->verticalLayout_5->count();i++){
            QWidget *widget = ui->verticalLayout_5->itemAt(i)->widget();

            if (widget != NULL)
              {
                widget->hide();
              }
        }
        for(int i =0 ; i<ui->verticalLayout_6->count();i++){
            QWidget *widget = ui->verticalLayout_6->itemAt(i)->widget();

            if (widget != NULL)
              {
                widget->hide();
              }
        }
        for(int i =0 ; i<ui->verticalLayout_7->count();i++){
            QWidget *widget = ui->verticalLayout_7->itemAt(i)->widget();

            if (widget != NULL)
              {
                widget->hide();
              }

        }
    }
    else if (num_Trans == 2){
        for(int i =0 ; i<ui->verticalLayout_6->count();i++){
            QWidget *widget = ui->verticalLayout_6->itemAt(i)->widget();

            if (widget != NULL)
              {
                widget->hide();
              }
        }
        for(int i =0 ; i<ui->verticalLayout_7->count();i++){
            QWidget *widget = ui->verticalLayout_7->itemAt(i)->widget();

            if (widget != NULL)
              {
                widget->hide();
              }

        }
    }
    else if (num_Trans == 3){

        for(int i =0 ; i<ui->verticalLayout_7->count();i++){
            QWidget *widget = ui->verticalLayout_7->itemAt(i)->widget();

            if (widget != NULL)
              {
                widget->hide();
              }

        }
    }

    for(int i=1 ; i<=4;i++){
        ui->Trans1_comboBox->addItem("Data Phase" + QString::number(i));
        ui->Trans2_comboBox->addItem("Data Phase" + QString::number(i));
        ui->Trans3_comboBox->addItem("Data Phase" + QString::number(i));
        ui->Trans4_comboBox->addItem("Data Phase" + QString::number(i));

    }
    //ui->Trans1_comboBox->setItemData(1, QSize(0,0), Qt::SizeHintRole);

}

subWindow::~subWindow()
{
    delete ui;
}


