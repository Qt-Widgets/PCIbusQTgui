#ifndef DEVICE_SIGNALS_H
#define DEVICE_SIGNALS_H

#include "QString"
#include "device.h"

class Device_Signals
{


public:
    bool secondTrans;

    Device_Signals();

    void set_controlSelect(QString control, int transaction_no);
    void set_targetSelect(DEVICE *target,int transaction_no);
    void set_numOfTrans(int numOfTrans);
    void set_numOfPhases(int transaction_no, int numOfPhases);
    void set_ByteEnable(int transaction_no , int DataPhase_no , QString byte_no);



    QString get_controlSelect();
    DEVICE* get_targetSelect();
    int get_numOfTrans();
    int get_numOfPhases(int transaction_no);
    QString get_ByteEnable(int transaction_no , int DataPhase_no);

    void decrementTrans();

private:
    //variables to save values chosen by the user

    QVector <QString> controlSelect;
    QVector <DEVICE*> targetSelect;
    QVector< QVector< QString > > DataPhases_ByteEnable;
    int numberOfTransactions;
};

#endif // DEVICE_SIGNALS_H
