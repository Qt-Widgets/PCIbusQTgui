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
       Clk+="10";
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

QChar PCI::GetFrame(){
    return Frame[Frame.size()-1];
}

QChar PCI::GetAD(){
    return AD[AD.size()-1];
}

QString PCI::GetData(){
    QString data="";
    for(int i =Data.size()-1;i>=0;i--)
    {
        if(Control_Byte[i]!='/')
            data+=Data[i];
        else
            break;
    }
    return data;
}

QChar PCI::GetCBE(){
    return CBE[CBE.size()-1];
}

QString PCI::GetControl_Byte(){
    QString control="";
    for(int i =Control_Byte.size()-1;i>=0;i--)
    {
        if(Control_Byte[i]!='/')
            control+=Control_Byte[i];
        else
            break;
    }
    return control;
}

QChar PCI::GetIRDY(){
    return IRDY[IRDY.size()-1];
}

QChar PCI::GetTRDY(){
    return TRDY[TRDY.size()-1];
}

QChar PCI::GetClk(int ClockEdge){
    return Clk[ClockEdge];
}

QChar PCI::GetReset(){
    return Reset[Reset.size()-1];
}

QChar PCI::GetDEVSEL(){
    return DEVSEL[DEVSEL.size()-1];
}

