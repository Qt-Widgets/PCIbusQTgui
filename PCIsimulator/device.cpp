#include "device.h"
#include <QDebug>

DEVICE::DEVICE()
{
    //Note: REQ And GNT are active low
    REQ = "1";
    GNT = "1";
    //initializing memory with xxxx
    DeviceMemory.resize(10);
    for(int i=0;i<10;i++) // 10 rowsof memory
    {
        for(int j=0;j<4;j++) // 4bytes in each row one word
        {
           DeviceMemory[i].append("x");
        }
    }
}
void DEVICE::setREQ(QChar forceREQ)
{
    REQ += forceREQ;
}
QString DEVICE::getREQ()
{
    return REQ;
}
void DEVICE::setGNT(QChar gnt)
{
    GNT += gnt;
}
QString DEVICE::getGNT()
{
    return GNT;
}



void DEVICE::SetMemoryByte(QString data,int rowIndex, int ByteIndex){

        DeviceMemory[rowIndex][ByteIndex]=data;
}

QString DEVICE::GetMemoryByte(int rowIndex, int ByteIndex){

    return  DeviceMemory[rowIndex][ByteIndex];
}







