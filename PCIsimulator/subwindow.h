#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QDialog>
#include <device_signals.h>


namespace Ui {
class subWindow;
}

class subWindow : public QDialog
{
    Q_OBJECT

public:
    explicit subWindow(QWidget *parent = 0, int num_Trans=0, QString Dev_name=" ",
                       Device_Signals *devA_main=0,Device_Signals *devB_main=0,Device_Signals *devC_main=0,Device_Signals *devD_main=0,
                       DEVICE *A=0,DEVICE *B=0, DEVICE *C=0,DEVICE *D=0);
    ~subWindow();
    QVector <Device_Signals*> devices_signals_sub ;

    Device_Signals *devA_sub,*devB_sub,*devC_sub,*devD_sub;
    DEVICE *DeviceA;
    DEVICE *DeviceB;
    DEVICE *DeviceC;
    DEVICE *DeviceD;

private slots:


    void on_Trans1_comboBox_currentIndexChanged(const QString &arg1);





    void on_Trans2_comboBox_currentIndexChanged(const QString &arg1);



    void on_Trans1_Target_currentTextChanged(const QString &arg1);

    void on_Trans2_Target_currentTextChanged(const QString &arg1);



    void on_Trans1_ReadRadio_clicked(bool checked);

    void on_Trans2_ReadRadio_clicked(bool checked);


    void on_Trans1_WriteRadio_clicked(bool checked);

    void on_Trans2_WriteRadio_clicked(bool checked);

    void on_Trans1_pushButton_clicked();

    void on_Trans2_pushButton_clicked(bool checked);




    void on_Trans1_Spinbox_editingFinished();
    void on_Trans2_Spinbox_editingFinished();




    void on_Apply_clicked();

private:
    Ui::subWindow *ui;



};

#endif // SUBWINDOW_H
