#include "device_signals.h"

Device_Signals::Device_Signals()
{
    masterSelect=" ";
    controlSelect=" ";
    numOfTrans=" ";
    targetSelect=" ";
    numOfPhases= " ";
    ByteEnable=" ";
}

void Device_Signals :: set_masterSelect(QString master){
    masterSelect = master;
}
void Device_Signals :: set_controlSelect(QString control){
    controlSelect = control;
}
void Device_Signals :: set_numOfTrans(QString number){
    numOfTrans = number;
}
void Device_Signals :: set_targetSelect(QString target){
    targetSelect = target;
}
void Device_Signals :: set_numOfPhases(QString number){
    numOfPhases = number;
}
void Device_Signals :: set_ByteEnable(QString byte_no){
    ByteEnable = byte_no;
}
QString Device_Signals ::  get_masterSelect(){return masterSelect;}
QString Device_Signals :: get_controlSelect(){return controlSelect;}
QString Device_Signals :: get_numOfTrans(){return numOfTrans;}
QString Device_Signals :: get_targetSelect(){return targetSelect;}
QString Device_Signals :: get_numOfPhases(){return numOfPhases;}
QString Device_Signals :: get_ByteEnable(){return ByteEnable;}

