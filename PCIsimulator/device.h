#ifndef DEVICE_H
#define DEVICE_H
#include <QChar>
#include<QString>

class DEVICE
{
    QString REQ;
    QString GNT;
public:
    //constructor
    DEVICE();

    void setREQ(QChar forceREQ);
    QString getREQ();

    void setGNT(QChar gnt);
    QString getGNT();
};

#endif // DEVICE_H
