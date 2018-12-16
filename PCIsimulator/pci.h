#ifndef PCI_H
#define PCI_H
#include <QString>
#include <QChar>

class PCI
{
public:
    PCI();
    void SetReset(QString bit);
    void SetFrame(QString bit);
    void SetAD(QString bit);
    void Setdata(QString bit);
    void SetCBE(QString bit);
    void SetControl_Byte(QString bit);
    void SetIRDY(QString bit);
    void SetTRDY(QString bit);
    void SetDEVSEL(QString bit);
    void SetClock(int NumberOfCycles);
    void SetPreviousBit(QString Signals);
    QChar GetFrameBit();
    QChar GetADBit();
    QString GetDataBit();
    QChar GetCBEBit();
    QString GetControl_ByteBit();
    QChar GetIRDYBit();
    QChar GetTRDYBit();
    QChar GetDEVSELBit();
    QChar GetClkBit(int ClockEdge);
    QChar GetResetBit();
    QString GetFrame();
    QString GetAD();
    QString GetData();
    QString GetCBE();
    QString GetControl_Byte();
    QString GetIRDY();
    QString GetTRDY();
    QString GetDEVSEL();
    QString GetClk();
    QString GetReset();


private:
   QString Frame;
   QString AD;
   QString Data;
   QString CBE;
   QString Control_Byte;
   QString IRDY;
   QString TRDY;
   QString DEVSEL;
   QString Clk;
   QString Reset;

};

#endif // PCI_H
