#include "pci.h"

PCI::PCI()
{
     Frame="1";
     AD="1";
     Data="x";
     CBE="1";
     Control_Byte="x";
     IRDY="1";
     TRDY="1";
     DEVSEL="1";
     Clk="1";
     Reset="1";
}


void PCI::SetClock(int NumberOfCycles){
    Clk="";
    for(int i = 0;i<NumberOfCycles;i++)
    {
       Clk+="01";
    }
}

void PCI::SetReset(QString bit){
    Reset+=bit;
}

void PCI::SetFrame(QString bit){
    Frame+=bit;
}
void PCI::SetAD(QString bit){
    AD+=bit;
}

void PCI::Setdata(QString bit){
    Data+=bit;
}

void PCI::SetCBE(QString bit){
    CBE+=bit;
}

void PCI::SetControl_Byte(QString bit){
    Control_Byte+=bit;
}

void PCI::SetIRDY(QString bit){
    IRDY+=bit;
}

void PCI::SetTRDY(QString bit){
    TRDY+=bit;
}

void PCI::SetDEVSEL(QString bit){
    DEVSEL+=bit;
}

QChar PCI::GetFrameBit(){
    return Frame[Frame.size()-1];
}

QChar PCI::GetADBit(){
    return AD[AD.size()-1];
}

QString PCI::GetDataBit(){
    QString data="";
    int NumberOfSlash=0;
    for(int i=0; i<Data.size();i++){
        if(Data[i]=='/')
            NumberOfSlash++;
    }

    for(int i=0; i<Data.size();i++)
    {
        if(Data[i]=='/')
            NumberOfSlash--;
        else if(NumberOfSlash==0)
            data+=Data[i];

    }
    return data;
}

QChar PCI::GetCBEBit(){
    return CBE[CBE.size()-1];
}

QString PCI::GetControl_ByteBit(){
    QString control="";
    int NumberOfSlash=0;
    for(int i=0; i<Control_Byte.size();i++){
        if(Control_Byte[i]=='/')
            NumberOfSlash++;
    }

    for(int i=0; i<Control_Byte.size();i++)
    {
        if(Control_Byte[i]=='/')
            NumberOfSlash--;
        else if(NumberOfSlash==0)
            control+=Control_Byte[i];

    }
    return control;
}

QChar PCI::GetIRDYBit(){
    return IRDY[IRDY.size()-1];
}

QChar PCI::GetTRDYBit(){
    return TRDY[TRDY.size()-1];
}

QChar PCI::GetClkBit(int ClockEdge){
    return Clk[ClockEdge];
}

QChar PCI::GetResetBit(){
    return Reset[Reset.size()-1];
}

QChar PCI::GetDEVSELBit(){
    return DEVSEL[DEVSEL.size()-1];
}
QString PCI::GetFrame(){
    return Frame;
}
QString PCI::GetAD(){
    return AD;
}
QString PCI::GetData(){
    return Data;
}
QString PCI::GetCBE(){
    return CBE;
}
QString PCI::GetControl_Byte(){
    return Control_Byte;
}
QString PCI::GetIRDY(){
    return IRDY;
}
QString PCI::GetTRDY(){
    return TRDY;
}
QString PCI::GetDEVSEL(){
    return DEVSEL;
}
QString PCI::GetClk(){
    return Clk;
}
QString PCI::GetReset(){
    return Reset;
}

void PCI::SetPreviousBit(QString Signals){
    QString Signalname="";
    for(int i=0;i<Signals.size();i++){
        if(Signals[i]!='/'){
            Signalname+=Signals[i];
        }
        else
        {
            if(Signalname=="Frame")
            {
                Frame+=Frame[Frame.size()-1];
            }
            else if(Signalname=="AD")
            {
                AD+="1";
            }
            else if(Signalname=="CBE")
            {
                CBE+="1";
            }
            else if(Signalname=="IRDY")
            {
                IRDY+=IRDY[IRDY.size()-1];
            }
            else if(Signalname=="TRDY")
            {
                TRDY+=TRDY[TRDY.size()-1];
            }
            else if(Signalname=="DEVSEL")
            {
                DEVSEL+=DEVSEL[DEVSEL.size()-1];
            }
            else if(Signalname=="Reset")
            {
                Reset+=Reset[Reset.size()-1];
            }
            Signalname="";
        }

    }
}










