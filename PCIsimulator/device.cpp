#include "device.h"
#include <QDebug>

DEVICE::DEVICE(QString name,QString pri)
{
    //Note: REQ And GNT are active low
    REQ = "1";
    GNT = "1";
    Name = name;
    masterFlag=false;
    //initializing memory with xxxx
    DeviceMemory.resize(10);
    for(int i=0;i<10;i++) // 10 rowsof memory
    {
        for(int j=0;j<4;j++) // 4bytes in each row one word
        {
           if(this->GetDeviceName()=="DeviceA")
               DeviceMemory[i].append("A");

           else if(this->GetDeviceName()=="DeviceB")
               DeviceMemory[i].append("B");

           else if(this->GetDeviceName()=="DeviceC")
               DeviceMemory[i].append("C");

           else if(this->GetDeviceName()=="DeviceD")
               DeviceMemory[i].append("D");
        }
    }
    priority=pri;
}
void DEVICE::SetREQ(QString bit)
{
    REQ += bit;
}
QString DEVICE::GetREQ()
{
    return REQ;
}
void DEVICE::SetGNT(QString bit)
{
    GNT += bit;
}
QString DEVICE::GetGNT()
{
    return GNT;
}
QChar DEVICE::GetGNTBit(){
    return GNT[GNT.size()-1];
}

QChar DEVICE::GetREQBit(){
    return REQ[REQ.size()-1];
}


void DEVICE::SetMemoryByte(QString data,int rowIndex, int ByteIndex){

        DeviceMemory[rowIndex][ByteIndex]=data;
}

QString DEVICE::GetMemoryByte(int rowIndex, int ByteIndex){

    return  DeviceMemory[rowIndex][ByteIndex];
}

QString DEVICE::GetDeviceName(){
    return Name;
}

QString DEVICE::GetMemoryWord(int rowIndex){
    QString data="";
    for(int i=0;i<4;i++)
    {
        if(i==0)
            data+="("+DeviceMemory[rowIndex][i];
        else if(i==3)
            data+="-"+DeviceMemory[rowIndex][i]+")";
        else
            data+="-"+DeviceMemory[rowIndex][i];

    }
    return data;
}

void DEVICE::SetMemoryWord(QString data, int rowIndex){
    QString value="";
    int coloumIndex=0;
    for(int i=0;i<data.size();i++)
    {

        if(data[i]!='-' && data[i]!='(' && data[i]!=')')
            value+=data[i];
        else
        {
            if(value=="")
                continue;
            DeviceMemory[rowIndex][coloumIndex]=value;
            value="";
            coloumIndex++;
        }
    }

}

void DEVICE::SetPreviousBit(QString Signals){
    QString Signalname="";
    for(int i=0;i<Signals.size();i++){
        if(Signals[i]!='/'){
            Signalname+=Signals[i];
        }
        else
        {
            if(Signalname=="GNT")
            {
                GNT+=GNT[GNT.size()-1];
            }
            else if(Signalname=="REQ")
            {
                REQ+=REQ[REQ.size()-1];
            }
            Signalname="";
        }

    }
}
// function to toggle the lastbit not append another bit to compenste the error of
// add bits of nonActive devices then add another bit to make gnt is low in rbiter function
void DEVICE::GNTtoggle(){

    if(GNT[GNT.size()-1]=='0')
    {
        GNT[GNT.size()-1]='1';
    }
    else if(GNT[GNT.size()-1]=='1')
    {
        GNT[GNT.size()-1]='0';
    }

}
void DEVICE::REQtoggle(){

    if(REQ[REQ.size()-1]=='0')
    {
        REQ[REQ.size()-1]='1';
    }
    else if(REQ[REQ.size()-1]=='1')
    {
        REQ[REQ.size()-1]='0';
    }

}

QString DEVICE::GetPriority(){
    return priority;
}

QString DEVICE::GetMemoryByteEnable(int rowIndex, QString byteEnable){
    QString data="";
    QString byte="";
    int byteIndex=0;
    for(int i=0;i<byteEnable.size();i++)
    {
        byte=byteEnable[i];
        byteIndex=byte.toInt()-1;
        if(i==0 && byteEnable.size()>1)
            data+="("+this->DeviceMemory[rowIndex][byteIndex];
        else if(i==byteEnable.size()-1 && byteEnable.size()>1)
            data+="-"+this->DeviceMemory[rowIndex][byteIndex]+")";
        else if(byteEnable.size()==1)
            data+="("+this->DeviceMemory[rowIndex][byteIndex]+")";
        else
            data+="-"+this->DeviceMemory[rowIndex][byteIndex];
    }
  return data;
}

void DEVICE::SetMemoryByteEnable(QString data, int rowIndex, QString byteEnable){

    QString value="";
    QString byteEnableIndex="";
    int byteIndex=0;
    int coloumIndex=0;
    for(int i=0;i<data.size();i++)
    {
        byteEnableIndex=byteEnable[coloumIndex];
        byteIndex=byteEnableIndex.toInt()-1;
        if(data[i]!='-' && data[i]!='(' && data[i]!=')')
            value+=data[i];
        else
        {
            if(value=="")
                continue;
            DeviceMemory[rowIndex][byteIndex]=value;
            value="";
            coloumIndex++;
        }
    }





}
