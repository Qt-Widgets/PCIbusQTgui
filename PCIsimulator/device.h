#ifndef DEVICE_H
#define DEVICE_H
#include <QChar>
#include<QString>
#include <QVector>

class DEVICE
{

public:
    //constructor
    DEVICE(QString);

    void setREQ(QChar forceREQ);
    QString getREQ();

    void setGNT(QChar gnt);
    QString getGNT();


    void SetMemoryByte(QString data,int rowIndex, int ByteIndex);
    void SetMemoryWord(QString data,int rowIndex);
    QString GetMemoryByte(int rowIndex, int ByteIndex);
    QString GetMemoryWord(int rowIndex);
    QString GetDeviceName();

private:
    QString Name;
    QString REQ;
    QString GNT;
    QVector< QVector< QString > > DeviceMemory;
};

#endif // DEVICE_H
