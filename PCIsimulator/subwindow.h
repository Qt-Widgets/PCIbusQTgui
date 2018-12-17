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
    explicit subWindow(QWidget *parent = 0, int num_Trans=0, QString Dev_name=" ");
    ~subWindow();

 Device_Signals DevA;

private slots:
    void on_Trans1_Spinbox_editingFinished();

    void on_Trans2_Spinbox_editingFinished();

    void on_Trans3_Spinbox_editingFinished();

    void on_Trans4_Spinbox_editingFinished();

    void on_Trans1_comboBox_currentIndexChanged(const QString &arg1);

    void on_Trans1_Target_currentTextChanged(const QString &arg1);

private:
    Ui::subWindow *ui;


};

#endif // SUBWINDOW_H
