#ifndef DEVICE_H
#define DEVICE_H
#include <QChar>
#include<QString>
#include <QVector>

class DEVICE
{

public:
    //constructor
    DEVICE(QString name,QString pri);

    void SetREQ(QString bit);
    QString GetREQ();
    QChar GetREQBit();
    void REQtoggle();

    void SetGNT(QString bit);
    QString GetGNT();
    QChar GetGNTBit();
    void GNTtoggle();

    void SetPreviousBit(QString Signals);

    void SetMemoryByte(QString data,int rowIndex, int ByteIndex);
    void SetMemoryWord(QString data,int rowIndex);
    QString GetMemoryByte(int rowIndex, int ByteIndex);
    QString GetMemoryWord(int rowIndex);
    QString GetDeviceName();

    QString GetPriority();
    bool masterFlag;

    QString GetMemoryByteEnable(int rowIndex,QString byteEnable);
    void SetMemoryByteEnable(QString data, int rowIndex, QString byteEnable);
private:
    QString Name;
    QString REQ;
    QString GNT;
    QVector< QVector< QString > > DeviceMemory;
    QString priority;

};

#endif // DEVICE_H
