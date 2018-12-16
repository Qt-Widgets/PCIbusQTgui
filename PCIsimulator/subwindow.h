#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QDialog>

namespace Ui {
class subWindow;
}

class subWindow : public QDialog
{
    Q_OBJECT

public:
    explicit subWindow(QWidget *parent = 0, int num_Trans=0);
    ~subWindow();

    void ComboBoxItems();




private slots:
    void on_Trans1_Spinbox_editingFinished();

    void on_Trans2_Spinbox_editingFinished();

    void on_Trans3_Spinbox_editingFinished();

    void on_Trans4_Spinbox_editingFinished();

private:
    Ui::subWindow *ui;
};

#endif // SUBWINDOW_H
