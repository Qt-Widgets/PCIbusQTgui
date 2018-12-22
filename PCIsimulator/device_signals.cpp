#include "device_signals.h"
#include"device.h"

Device_Signals::Device_Signals()
{

}


void Device_Signals :: set_controlSelect(QString control,int transaction_no){
    controlSelect[transaction_no] = control;
}
void Device_Signals :: set_targetSelect(DEVICE *target, int transaction_no){
    targetSelect[transaction_no]=target;
}
void Device_Signals :: set_numOfTrans(int numOfTrans){
    DataPhases_ByteEnable.resize(numOfTrans);
    targetSelect.resize(numOfTrans);
    controlSelect.resize(numOfTrans);
    numberOfTransactions=numOfTrans;
    if(numberOfTransactions==2)
        secondTrans=true;
    else
        secondTrans=false;
}

void Device_Signals :: set_numOfPhases(int transaction_no, int numOfPhases){

    DataPhases_ByteEnable[transaction_no].resize(numOfPhases);

    for(int j=0;j<numOfPhases;j++){
        DataPhases_ByteEnable[transaction_no][j]="1234";
    }

}
void Device_Signals ::set_ByteEnable(int transaction_no , int DataPhase_no , QString byte_no){
    DataPhases_ByteEnable[transaction_no][DataPhase_no] = byte_no;
}


QString Device_Signals :: get_controlSelect(){
    QString temp="";
    if(!controlSelect.isEmpty())
    {
        temp=controlSelect.front();
        controlSelect.pop_front();
    }
    else
        return 0;
    return temp;
}
DEVICE* Device_Signals :: get_targetSelect(){
    DEVICE* temp=new DEVICE("temp","-1");
    if(!targetSelect.isEmpty())
    {
        temp=targetSelect.front();
        targetSelect.pop_front();
    }
    else
        return 0;
    return temp;
}
int Device_Signals :: get_numOfTrans(){
    return numberOfTransactions;
}
int Device_Signals :: get_numOfPhases(int transaction_no){
    return DataPhases_ByteEnable[transaction_no].size();
}
QString Device_Signals :: get_ByteEnable(int transaction_no , int DataPhase_no)
{
    return DataPhases_ByteEnable[transaction_no][DataPhase_no];
}

void Device_Signals ::decrementTrans(){
    numberOfTransactions--;

}
