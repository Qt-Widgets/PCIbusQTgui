#ifndef DEVICE_SIGNALS_H
#define DEVICE_SIGNALS_H

#include "QString"

class Device_Signals
{


public:
    Device_Signals();
    void set_masterSelect(QString master);
    void set_controlSelect(QString control);
    void set_numOfTrans(QString number);
    void set_targetSelect(QString target);
    void set_numOfPhases(QString number);
    void set_ByteEnable(QString byte_no);


    QString get_masterSelect();
    QString get_controlSelect();
    QString get_numOfTrans();
    QString get_targetSelect();
    QString get_numOfPhases();
    QString get_ByteEnable();

private:
    //variables to save values chosen by the user
    QString masterSelect ;
    QString controlSelect;
    QString numOfTrans;
    QString targetSelect;
    QString numOfPhases;
    QString ByteEnable;
};

#endif // DEVICE_SIGNALS_H
