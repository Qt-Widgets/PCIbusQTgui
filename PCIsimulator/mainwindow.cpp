#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view.h"
#include "device.h"
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
    QVector<QString> signal;
    QString input = "1010101010101010";


    QVector<QString> name;
    name.append("clk");
    signal.append(input);
    Graph=new View(0,signal,name,6);
    Graph->show();

    DEVICE *amir = new DEVICE();


}

