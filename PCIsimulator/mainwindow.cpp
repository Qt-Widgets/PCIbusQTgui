#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view.h"

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
    name.append("frame");
    name.append("AD");
    name.append("data");
    name.append("amir");

    name.append("asd");
    name.append("C/BE");
    name.append("data");
    signal.append(input);
     input = "x1xx110x01x0";
    signal.append(input);




    signal.append("11/1/1/1");
    signal.append("63/x/616/dasd");

    signal.append(input);
    signal.append(input);
    signal.append("1xx11/1");
    signal.append("63/x/616/dasd");

    Graph=new View(0,signal,name,6);
    Graph->show();
}
