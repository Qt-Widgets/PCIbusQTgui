#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view.h"
#include "device.h"
#include <QDebug>
#include <subwindow.h>

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
    QVector<QString> signal;
    QString input = "1010101010101010";


    QVector<QString> name;
    name.append("clk");
    signal.append(input);
    Graph=new View(0,signal,name,6);
    Graph->show();

    DEVICE *amir = new DEVICE();


}


void MainWindow::on_DevA_spinBox_editingFinished()
{
    SubWindow = new subWindow(this,ui->DevA_spinBox->value());
    SubWindow->setModal(true);
    if(ui->DevA_spinBox->value() != 0){
    SubWindow->exec();
    }
}

void MainWindow::on_DevB_spinBox_editingFinished()
{
    SubWindow = new subWindow(this,ui->DevB_spinBox->value());
    SubWindow->setModal(true);
    if(ui->DevB_spinBox->value() != 0){
    SubWindow->exec();
    }
}

void MainWindow::on_DevC_spinBox_editingFinished()
{
    SubWindow = new subWindow(this,ui->DevC_spinBox->value());
    SubWindow->setModal(true);
    if(ui->DevC_spinBox->value() != 0){
    SubWindow->exec();
    }
}



void MainWindow::on_DevD_spinBox_editingFinished()
{
    SubWindow = new subWindow(this,ui->DevD_spinBox->value());
    SubWindow->setModal(true);
    if(ui->DevD_spinBox->value() != 0){
    SubWindow->exec();
    }
}
