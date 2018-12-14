#ifndef DEVICE_H
#define DEVICE_H
#include <QChar>
#include<QString>
#include <QVector>

class DEVICE
{

public:
    //constructor
    DEVICE();

    void setREQ(QChar forceREQ);
    QString getREQ();

    void setGNT(QChar gnt);
    QString getGNT();


    void SetMemoryByte(QString data,int rowIndex, int ByteIndex);
    QString GetMemoryByte(int rowIndex, int ByteIndex);

private:
    QString REQ;
    QString GNT;
    QVector< QVector< QString > > DeviceMemory;
};

#endif // DEVICE_H
