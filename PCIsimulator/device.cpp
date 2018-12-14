#include "device.h"

DEVICE::DEVICE()
{
    //Note: REQ And GNT are active low
    REQ = 1;
    GNT= 1;
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
