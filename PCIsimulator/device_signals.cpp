#include "device_signals.h"
#include"device.h"

Device_Signals::Device_Signals()
{
    targetSelect.resize(2);
    controlSelect.resize(2);

}


void Device_Signals :: set_controlSelect(QString control,int transaction_no){
    controlSelect[transaction_no] = control;
}
void Device_Signals :: set_targetSelect(DEVICE *target, int transaction_no){
    targetSelect[transaction_no]=target;
}
void Device_Signals :: set_numOfTrans(int numOfTrans){
    DataPhases_ByteEnable.resize(numOfTrans);
}
void Device_Signals :: set_numOfPhases(int transaction_no, int numOfPhases){

    DataPhases_ByteEnable[transaction_no].resize(numOfPhases);
}
void Device_Signals ::set_ByteEnable(int transaction_no , int DataPhase_no , char byte_no){
    DataPhases_ByteEnable[transaction_no][DataPhase_no] += byte_no;
}

QVector<QString> Device_Signals :: get_controlSelect(){
    return controlSelect;
}
QVector <DEVICE*> Device_Signals :: get_targetSelect(){
    return targetSelect;
}
int Device_Signals :: get_numOfTrans(){
    return DataPhases_ByteEnable.size();
}
int Device_Signals :: get_numOfPhases(int transaction_no){
    return DataPhases_ByteEnable[transaction_no].size();
}
QString Device_Signals :: get_ByteEnable(int transaction_no , int DataPhase_no)
{
    return DataPhases_ByteEnable[transaction_no][DataPhase_no];
}

