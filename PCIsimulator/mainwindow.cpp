#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view.h"
#include "device.h"
#include "pci.h"
#include <subwindow.h>
#include"device_signals.h"
#include <QDebug>
#include<QMessageBox>
#include <QAction>

int const MainWindow::EXIT_CODE_REBOOT = -123456789;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    DeviceA=new DEVICE("DeviceA","4");
    DeviceB=new DEVICE("DeviceB","3");
    DeviceC=new DEVICE("DeviceC","2");
    DeviceD=new DEVICE("DeviceD","1");
    devA_main=new Device_Signals();
    devB_main=new Device_Signals();
    devC_main=new Device_Signals();
    devD_main=new Device_Signals();

    ui->DevA_IdleRadio->setChecked(true);
    ui->DevB_IdleRadio->setChecked(true);
    ui->DevC_IdleRadio->setChecked(true);
    ui->DevD_IdleRadio->setChecked(true);
    mainBus = new PCI();
    master=new DEVICE("master","0");
    endTransaction=false;
    beginTransaction=true;
    firstMaster=true;
    allgnt=true;
    otherReq=false;
    gnthigh=false; // a bool to take the grant from master after frame is low
    senarioFlag=false;
    nonActiveControl.resize(3);
    dataCounter=0;
    arbiterMoodIndex=0;


    actionReboot = new QAction( this );
    actionReboot->setText( tr("Restart") );
    actionReboot->setStatusTip( tr("Restarts the application") );
    connect( actionReboot, SIGNAL (triggered()),
                     this, SLOT (on_pushButton_2_clicked())
           );

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    ByteEnable.append(2);
    ByteEnable.append(3);
    Transaction="Read";

    numberOfTrnsaction=1;

    numberOfTransfers=1;




    /****************************************************************************************************/
    //ArbiterFunction



    if(senarioFlag)
    {
        if(arbiterMoodIndex==0)
            MainWindow::FCFS(0,100);
        else
            MainWindow::Priority(0,100);




        mainBus->SetClock(mainCounter/2);
        Signals.append(mainBus->GetDEVSEL());
        Signals.append(mainBus->GetTRDY());
        Signals.append(mainBus->GetIRDY());
        Signals.append(mainBus->GetCBE());
        Signals.append(mainBus->GetControl_Byte());
        Signals.append(mainBus->GetAD());
        Signals.append(mainBus->GetData());
        Signals.append(mainBus->GetFrame());


        for(int i=0;i<4;i++)
        {
            if(i==0)
            {
               if(master->GetDeviceName()=="DeviceD")
               {
                  Signals.append(master->GetGNT());
                  Signals.append(master->GetREQ());
                  continue;
               }
               for(int j=0;j<nonActive.size();j++)
               {
                   if(nonActive[j]->GetDeviceName()=="DeviceD")
                   {
                     Signals.append(nonActive[j]->GetGNT());
                     Signals.append(nonActive[j]->GetREQ());
                     break;
                   }
               }
            }
            else if (i==1)
            {
                if(master->GetDeviceName()=="DeviceC")
                {
                   Signals.append(master->GetGNT());
                   Signals.append(master->GetREQ());
                   continue;
                }
                for(int j=0;j<nonActive.size();j++)
                {
                    if(nonActive[j]->GetDeviceName()=="DeviceC")
                    {
                      Signals.append(nonActive[j]->GetGNT());
                      Signals.append(nonActive[j]->GetREQ());
                      break;
                    }
                }
            }
            else if(i==2)
            {
                if(master->GetDeviceName()=="DeviceB")
                {
                   Signals.append(master->GetGNT());
                   Signals.append(master->GetREQ());
                   continue;
                }
                for(int j=0;j<nonActive.size();j++)
                {
                    if(nonActive[j]->GetDeviceName()=="DeviceB")
                    {
                      Signals.append(nonActive[j]->GetGNT());
                      Signals.append(nonActive[j]->GetREQ());
                      break;
                    }
                }
            }
            else if(i==3)
            {
                if(master->GetDeviceName()=="DeviceA")
                {
                   Signals.append(master->GetGNT());
                   Signals.append(master->GetREQ());
                   continue;
                }
                for(int j=0;j<nonActive.size();j++)
                {
                    if(nonActive[j]->GetDeviceName()=="DeviceA")
                    {
                      Signals.append(nonActive[j]->GetGNT());
                      Signals.append(nonActive[j]->GetREQ());
                      break;
                    }
                }
            }
        }


        Signals.append(mainBus->GetClk());







        SignalsNames.append("DEVSEL");
        SignalsNames.append("TRDY");
        SignalsNames.append("IRDY");
        SignalsNames.append("CBE");
        SignalsNames.append("Control_Byte");
        SignalsNames.append("AD");
        SignalsNames.append("Data");
        SignalsNames.append("Frame");

        SignalsNames.append("GNT D");
        SignalsNames.append("REQ D");
        SignalsNames.append("GNT C");
        SignalsNames.append("REQ C");
        SignalsNames.append("GNT B");
        SignalsNames.append("REQ B");
        SignalsNames.append("GNT A");
        SignalsNames.append("REQ A");
        SignalsNames.append("Clk");
        Graph=new View(0,Signals,SignalsNames,(mainCounter/2));
        Graph->show();
    }
    else
    {
        QMessageBox::warning(this,"Senario Error","You Didnot Submit Any Senarios");
    }


}


void MainWindow::Priority(int begin, int end){
bool secondTrans=false;
    if(begin==0){
        begin=1;
    }
    else
    {
        begin*=2;
    }

    for(mainCounter=begin;mainCounter<(end*2);mainCounter++)
    {
        if(mainCounter%2==0) // at negative edge
        {
            //contion at delay time if yes go and make the req of masterSelect signal low
            //and if end transction is true change master
            if(mainCounter==(delay.head()+1)*2 && master->GetDeviceName()=="master")
            {

                    master=MastersSelect.head();
                    masterControl=MastersControl.head();
                    numberOfTransfers=masterControl->get_numOfPhases(0);
                    masterTarget=masterControl->get_targetSelect();
                    Transaction=masterControl->get_controlSelect();

                    master->SetREQ("0");
                    master->SetPreviousBit("GNT/");
                    if(MastersSelect.head()!=DeviceA)
                    {
                        nonActive.append(DeviceA);
                    }
                    if(MastersSelect.head()!=DeviceB)
                    {
                        nonActive.append(DeviceB);
                    }
                    if(MastersSelect.head()!=DeviceC)
                    {
                        nonActive.append(DeviceC);
                    }
                    if(MastersSelect.head()!=DeviceD)
                    {
                        nonActive.append(DeviceD);
                    }
                    for(int i=0;i<nonActive.size();i++)
                    {
                        nonActive[i]->SetPreviousBit("GNT/REQ/");
                    }

                    if(delay.size()>1)
                    {
                        delay.dequeue();
                        MastersSelect.dequeue();
                        MastersControl.dequeue();

                    }

                    mainBus->SetPreviousBit("Frame/AD/CBE/IRDY/TRDY/DEVSEL/Reset/");
            }
            else
            {
                //condition for the device req when a another device have the  bus so we make its req is low
                if(mainCounter==(delay.head()+1)*2)
                {
                    for(int i=0;i<nonActive.size();i++)
                    {
                        nonActive[i]->SetPreviousBit("GNT/REQ/");
                    }
                    int delays=delay.size();
                    for(int i=0;i<delays;i++)
                    {
                        if(MastersSelect.head()==nonActive[0] && mainCounter==(delay.head()+1)*2 )
                        {
                            queueP.enqueue(nonActive[0]->GetPriority()+"/"+QString::number(delay.head())+"/0");
                            MainWindow::SortPriority();
                            nonActiveControl[0]=MastersControl.head();
                            if(delay.size()>1)
                            {
                                delay.dequeue();
                                MastersSelect.dequeue();
                                MastersControl.dequeue();
                            }
                            nonActive[0]->REQtoggle();
                            otherReq=true;
                        }
                        else if(MastersSelect.head()==nonActive[1]&& mainCounter==(delay.head()+1)*2)
                        {
                            queueP.enqueue(nonActive[1]->GetPriority()+"/"+QString::number(delay.head())+"/1");
                            MainWindow::SortPriority();
                            nonActiveControl[1]=MastersControl.head();
                            if(delay.size()>1)
                            {
                                delay.dequeue();
                                MastersSelect.dequeue();
                                MastersControl.dequeue();
                            }
                            nonActive[1]->REQtoggle();
                            otherReq=true;

                        }
                        else if(MastersSelect.head()==nonActive[2]&& mainCounter==(delay.head()+1)*2)
                        {
                            queueP.enqueue(nonActive[2]->GetPriority()+"/"+QString::number(delay.head())+"/2");
                            MainWindow::SortPriority();
                            nonActiveControl[2]=MastersControl.head();
                            if(delay.size()>1)
                            {
                                delay.dequeue();
                                MastersSelect.dequeue();
                                MastersControl.dequeue();
                            }
                            nonActive[2]->REQtoggle();
                            otherReq=true;
                        }

                    }

                }
                // if the master req second trans and its prior
                else if(endTransaction && secondTrans && !queueP.isEmpty())
                {
                    if(queueP.head()[1]=='m')
                    {
                        if(masterControl->get_numOfTrans()==1)
                        {
                           numberOfTransfers=masterControl->get_numOfPhases(1);
                        }
                        else
                        {
                            numberOfTransfers=masterControl->get_numOfPhases(0);
                        }

                        masterTarget=masterControl->get_targetSelect();
                        Transaction=masterControl->get_controlSelect();

                        endTransaction=false;
                        secondTrans=false;

                        for(int i=0;i<nonActive.size();i++)
                        {
                            nonActive[i]->SetPreviousBit("GNT/REQ/");
                        }
                        if(!queueP.isEmpty())
                            queueP.dequeue();
                    }
                    else
                    {
                        for(int i=0;i<nonActive.size();i++)
                        {
                            nonActive[i]->SetPreviousBit("GNT/REQ/");
                            secondTrans=false;
                        }
                    }
                }
                //condition for changing master with the device in the queue
                 else if(endTransaction && !queueP.isEmpty())
                {
                    DEVICE *temp=new DEVICE("temp",0);
                    temp=master;

                    Device_Signals *tempControl=new Device_Signals();
                    tempControl=masterControl;



                    nonActiveIndex="";
                    nonActiveIndex=queueP.head()[4];


                    if(findMaster()>-1)
                    {
                        int masterIndex=findMaster();
                        queueP[masterIndex][1]='/';
                        queueP[masterIndex]+="/"+nonActiveIndex;
                    }

                    master=nonActive[nonActiveIndex.toInt()];
                    masterControl=nonActiveControl[nonActiveIndex.toInt()];




                    nonActive[nonActiveIndex.toInt()]=temp;
                    nonActiveControl[nonActiveIndex.toInt()]=tempControl;

                    for(int i=0;i<nonActive.size();i++)
                    {
                        nonActive[i]->SetPreviousBit("GNT/REQ/");
                    }

                    endTransaction=false;

                    if(masterControl->get_numOfTrans()==2)
                    {
                       numberOfTransfers=masterControl->get_numOfPhases(0);
                    }
                    else if (masterControl->get_numOfTrans()==1)
                    {
                        if(masterControl->secondTrans)
                           numberOfTransfers=masterControl->get_numOfPhases(1);
                        else
                           numberOfTransfers=masterControl->get_numOfPhases(0);
                    }

                    if(!queueP.isEmpty())
                        queueP.dequeue();

                    masterTarget=masterControl->get_targetSelect();
                    Transaction=masterControl->get_controlSelect();

                    if(allgnt)
                    {
                        master->SetGNT("0");
                        master->SetPreviousBit("REQ/");
                        mainBus->SetPreviousBit("Frame/AD/CBE/IRDY/TRDY/DEVSEL/Reset/");
                        continue;
                    }
                }

                else if(queueP.isEmpty() && MastersSelect.size()==1 && endTransaction && masterControl->get_numOfTrans()==0)
                {
                    break;
                }
                else
                {

                    for(int i=0;i<nonActive.size();i++)
                    {
                        nonActive[i]->SetPreviousBit("GNT/REQ/");
                    }
                }

                //condition to make gnt low for head of queueP device if isnot already low
                QString time="";
                if(!queueP.isEmpty() && otherReq)
                {
                    nonActiveIndex=queueP.head()[4];
                    if(nonActive[nonActiveIndex.toInt()]->GetGNTBit()!='0'&& queueP.head()[1]!='m')
                    {
                        time=queueP.head()[2];
                        if(mainCounter!=(time.toInt()+1)*2 && allgnt&& master->GetGNTBit()!='0')
                        {
                            nonActive[nonActiveIndex.toInt()]->GNTtoggle();
                        }
                        else if (mainCounter!=(time.toInt()+1)*2 && !allgnt && master->GetGNTBit()!='0')
                        {
                            for(int i=0;i<nonActive.size();i++)
                            {
                                if(nonActive[i]->GetGNTBit()=='0')
                                {
                                    nonActive[i]->GNTtoggle();
                                }
                            }
                            nonActive[nonActiveIndex.toInt()]->GNTtoggle();
                        }
                    }
                }
                //condition to make gnt low for the first master only
                if(master->GetREQBit()=='0' && firstMaster)
                {
                    master->SetGNT("0");
                    allgnt=false;
                    firstMaster=false;
                    master->SetPreviousBit("REQ/");
                    mainBus->SetPreviousBit("Frame/AD/CBE/IRDY/TRDY/DEVSEL/Reset/");
                }
                else if((master->GetGNTBit()=='0' && mainBus->GetFrameBit()=='1' && mainBus->GetIRDYBit()=='1') || !endTransaction)
                {

                    if(mainBus->GetFrameBit()=='0' && master->GetGNTBit()=='0' && masterControl->get_numOfTrans()==0)
                    {
                        if(masterControl->get_numOfTrans()==0)
                        {
                            master->SetGNT("1");
                            master->SetREQ("1");
                            allgnt=true;
                        }
                        if(!queueP.isEmpty())
                        {
                            time=queueP.head()[2];
                            nonActiveIndex=queueP.head()[4];
                            if(mainCounter!=(time.toInt()+1)*2 && nonActive[nonActiveIndex.toInt()]->GetGNTBit()!='0')
                            {
                                nonActive[nonActiveIndex.toInt()]->GNTtoggle();
                                allgnt=false;
                            }

                        }

                        gnthigh=true;
                    }
                    else if (mainBus->GetFrameBit()=='0' && mainBus->GetIRDYBit()=='1' && master->GetGNTBit()=='0' && masterControl->get_numOfTrans()==1)
                    {
                       if(MainWindow::masterIsPrior())
                       {

                           master->SetPreviousBit("GNT/REQ/");
                           secondTrans=true;
                           allgnt=false;
                           queueP.enqueue(master->GetPriority()+"m"+QString::number((mainCounter/2)-1));
                           MainWindow::SortPriority();
                       }
                       else
                       {
                           master->SetGNT("1");
                           master->SetPreviousBit("REQ/");
                           if(!queueP.isEmpty())
                           {
                               time=queueP.head()[2];
                               nonActiveIndex=queueP.head()[4];
                               if(mainCounter!=(time.toInt()+1)*2 && nonActive[nonActiveIndex.toInt()]->GetGNTBit()!='0')
                               {
                                   nonActive[nonActiveIndex.toInt()]->GNTtoggle();
                                   allgnt=false;
                               }

                           }
                           queueP.enqueue(master->GetPriority()+"m"+QString::number((mainCounter/2)-1));
                           MainWindow::SortPriority();
                       }
                        gnthigh=true;
                    }
                    endTransaction=false;
                    if(Transaction=="Read")
                    {
                       MainWindow::ReadTransaction(master,masterTarget);
                       if(!gnthigh)
                       {
                           master->SetPreviousBit("GNT/REQ/");

                       }
                        gnthigh=false;
                    }
                    else if(Transaction=="Write")
                    {
                       MainWindow::WriteTransaction(master,masterTarget);
                       if(!gnthigh)
                       {
                           master->SetPreviousBit("GNT/REQ/");
                           gnthigh=false;
                       }
                        gnthigh=false;
                    }
                }

                // condition to append to main bus when the transaction ends and i don't enter
                //the condition of READ and WRITE
                else if (mainBus->GetFrameBit()=='1' && mainBus->GetIRDYBit()=='1'&& endTransaction)
                {
                    mainBus->SetPreviousBit("Frame/AD/CBE/IRDY/TRDY/DEVSEL/Reset/");
                }
            }
        }
        else // at postive edge
        {
            if(mainCounter==1)
            {
                DeviceA->SetPreviousBit("GNT/REQ/");
                DeviceB->SetPreviousBit("GNT/REQ/");
                DeviceC->SetPreviousBit("GNT/REQ/");
                DeviceD->SetPreviousBit("GNT/REQ/");
                mainBus->SetPreviousBit("Frame/AD/CBE/IRDY/TRDY/DEVSEL/Reset/");
            }
            else
            {
                master->SetPreviousBit("GNT/REQ/");
                for(int i=0;i<nonActive.size();i++)
                {
                    nonActive[i]->SetPreviousBit("GNT/REQ/");
                }
                mainBus->SetPreviousBit("Frame/AD/CBE/IRDY/TRDY/DEVSEL/Reset/");
            }

        }
    }
}


void MainWindow::SortPriority(){

    int size=queueP.size();
    QString bit="";
    int queueI=0;
    int queueJ=0;
    for(int i=0;i<size;i++)
    {
        bit=queueP[i][0];
        queueI=bit.toInt();
      for(int j=i+1;j<size;j++)
      {
          bit=queueP[j][0];
          queueJ=bit.toInt();
          if(queueI<queueJ)
          {
              QString temp="";
              temp=queueP[i];
              queueP[i]=queueP[j];
              queueP[j]=temp;
              bit=queueP[i][0];
              queueI=bit.toInt();
          }
      }
    }

}

int MainWindow::findMaster(){

    for(int i=0;i<queueP.size();i++)
    {
       if(queueP[i][1]=='m')
           return i;
    }
    return -1;
}

bool MainWindow::masterIsPrior(){
    QString masterprio=master->GetPriority();
    int masterprioInt=masterprio.toInt();
    QString queuePrio="";
    int queuePrioInt=0;
    for(int i=0;i<queueP.size();i++)
    {
        queuePrio=queueP[i][0];
        queuePrioInt=queuePrio.toInt();
        if(masterprioInt<queuePrioInt)
            return false;
    }
    return true;
}




void MainWindow::FCFS(int begin, int end){
    if(begin==0){
        begin=1;
    }
    else
    {
        begin*=2;
    }
    bool continueTrans=false;

    for(mainCounter=begin;mainCounter<(end*2);mainCounter++)
    {
        if(mainCounter%2==0) // at negative edge
        {
            //contion at delay if yes go and make the req of masterSelect signal low
            //and if end transction is true change master
            if(mainCounter==(delay.head()+1)*2 && master->GetDeviceName()=="master")
            {
                    master=MastersSelect.head();
                    masterControl=MastersControl.head();
                    numberOfTransfers=masterControl->get_numOfPhases(0);
                    masterTarget=masterControl->get_targetSelect();
                    Transaction=masterControl->get_controlSelect();
                    master->SetREQ("0");
                    master->SetPreviousBit("GNT/");
                    if(MastersSelect.head()!=DeviceA)
                    {
                        nonActive.append(DeviceA);
                    }
                    if(MastersSelect.head()!=DeviceB)
                    {
                        nonActive.append(DeviceB);
                    }
                    if(MastersSelect.head()!=DeviceC)
                    {
                        nonActive.append(DeviceC);
                    }
                    if(MastersSelect.head()!=DeviceD)
                    {
                        nonActive.append(DeviceD);
                    }
                    for(int i=0;i<nonActive.size();i++)
                    {
                        nonActive[i]->SetPreviousBit("GNT/REQ/");
                    }
                    if(delay.size()>1)
                    {
                        delay.dequeue();
                        MastersSelect.dequeue();
                        MastersControl.dequeue();
                    }

                    mainBus->SetPreviousBit("Frame/AD/CBE/IRDY/TRDY/DEVSEL/Reset/");
            }
            else
            {
                //condition for the device req when a another device have the  bus so we make its req is low
                if(mainCounter==(delay.head()+1)*2)
                {
                    for(int i=0;i<nonActive.size();i++)
                    {
                        nonActive[i]->SetPreviousBit("GNT/REQ/");
                    }
                    int delays=delay.size();
                    for(int i=0;i<delays;i++)
                    {
                        if(MastersSelect.head()==nonActive[0] && mainCounter==(delay.head()+1)*2 )
                        {
                            queue.enqueue(0);
                            nonActiveControl[0]=MastersControl.head();
                            queueTime.enqueue(delay.head());
                            if(delay.size()>1)
                            {
                                delay.dequeue();
                                MastersSelect.dequeue();
                                MastersControl.dequeue();
                            }
                            nonActive[0]->REQtoggle();

                            otherReq=true;

                        }
                        else if(MastersSelect.head()==nonActive[1]&& mainCounter==(delay.head()+1)*2)
                        {
                            queue.enqueue(1);
                            nonActiveControl[1]=MastersControl.head();
                            queueTime.enqueue(delay.head());
                            if(delay.size()>1)
                            {
                                delay.dequeue();
                                MastersSelect.dequeue();
                                MastersControl.dequeue();
                            }
                            nonActive[1]->REQtoggle();

                            otherReq=true;


                        }
                        else if(MastersSelect.head()==nonActive[2]&& mainCounter==(delay.head()+1)*2)
                        {
                            queue.enqueue(2);
                            nonActiveControl[2]=MastersControl.head();
                            queueTime.enqueue(delay.head());
                            if(delay.size()>1)
                            {
                                delay.dequeue();
                                MastersSelect.dequeue();
                                MastersControl.dequeue();
                            }
                            nonActive[2]->REQtoggle();

                            otherReq=true;
                        }

                    }

                }
                //condition for changing master with the device in the queue
                else if(endTransaction && !queue.isEmpty())
                {
                    DEVICE *temp=new DEVICE("temp",0);
                    temp=master;
                    Device_Signals *tempControl=new Device_Signals();

                    int nonActiveIndex=queue.dequeue();

                    tempControl=masterControl;


                    if(master->GetREQBit()=='0' && masterControl->get_numOfTrans()!=0)
                    {
                        queue.enqueue(nonActiveIndex);
                        otherReq=true;
                    }


                    master=nonActive[nonActiveIndex];
                    masterControl=nonActiveControl[nonActiveIndex];

                    if(masterControl->get_numOfTrans()==2)
                    {
                       numberOfTransfers=masterControl->get_numOfPhases(0);
                    }
                    else if (masterControl->get_numOfTrans()==1)
                    {
                        if(masterControl->secondTrans)
                           numberOfTransfers=masterControl->get_numOfPhases(1);
                        else
                           numberOfTransfers=masterControl->get_numOfPhases(0);
                    }

                    masterTarget=masterControl->get_targetSelect();
                    Transaction=masterControl->get_controlSelect();
                    master->masterFlag=false;


                    nonActive[nonActiveIndex]=temp;
                    nonActiveControl[nonActiveIndex]=tempControl;


                    for(int i=0;i<nonActive.size();i++)
                    {
                        nonActive[i]->SetPreviousBit("GNT/REQ/");
                    }
                    if(MastersControl.size()>1)
                    {
                        MastersControl.dequeue();
                    }

                    endTransaction=false;
                    continueTrans=false;
                    dataCounter=0;

                    if(allgnt)
                    {
                        master->SetGNT("0");
                        master->SetPreviousBit("REQ/");
                        mainBus->SetPreviousBit("Frame/AD/CBE/IRDY/TRDY/DEVSEL/Reset/");
                        continue;
                    }
                }
                else if(endTransaction && continueTrans)
                {
                    numberOfTransfers=masterControl->get_numOfPhases(1);
                    masterTarget=masterControl->get_targetSelect();
                    Transaction=masterControl->get_controlSelect();
                    endTransaction=false;
                    continueTrans=false;
                    for(int i=0;i<nonActive.size();i++)
                    {
                        nonActive[i]->SetPreviousBit("GNT/REQ/");
                    }
                }
                else if(queue.isEmpty() && MastersSelect.size()==1 && endTransaction &&masterControl->get_numOfTrans()==0)
                {
                    break;
                }
                else
                {

                    for(int i=0;i<nonActive.size();i++)
                    {
                        nonActive[i]->SetPreviousBit("GNT/REQ/");
                    }
                }

                //condition to make gnt low for the requested device
                if(!queue.isEmpty() && allgnt && otherReq && !queueTime.isEmpty())
                {
                    if(mainCounter!=(queueTime.head()+1)*2)
                    {
                            nonActive[queue.head()]->GNTtoggle();
                            queueTime.dequeue();
                            otherReq=false;
                            allgnt=false;
                    }
                }

                //condition to make gnt low for the first master only
                if(master->GetREQBit()=='0' && firstMaster)
                {
                    master->SetGNT("0");
                    allgnt=false;
                    firstMaster=false;
                    master->SetPreviousBit("REQ/");
                    mainBus->SetPreviousBit("Frame/AD/CBE/IRDY/TRDY/DEVSEL/Reset/");
                }
                else if((master->GetGNTBit()=='0' && mainBus->GetFrameBit()=='1' && mainBus->GetIRDYBit()=='1') || !endTransaction)
                {
                    if(mainBus->GetFrameBit()=='0' && master->GetGNTBit()=='0')
                    {

                        allgnt=true;
                        if(!queue.isEmpty() && !queueTime.isEmpty())
                        {
                            master->SetGNT("1");
                            if(mainCounter!=(queueTime.head()+1)*2)
                            {
                                nonActive[queue.head()]->GNTtoggle();
                                allgnt=false;
                            }
                        }
                        else if(queue.isEmpty() && masterControl->get_numOfTrans()!=0)
                        {
                            master->SetPreviousBit("GNT/");
                            continueTrans=true;
                        }
                        if(masterControl->get_numOfTrans()==0)
                        {
                            if(allgnt)
                                master->SetGNT("1");
                            master->SetREQ("1");
                        }
                        else
                             master->SetPreviousBit("REQ/");
                        gnthigh=true;
                    }
                    endTransaction=false;
                    if(Transaction=="Read")
                    {
                       MainWindow::ReadTransaction(master,masterTarget);
                       if(!gnthigh)
                       {
                           master->SetPreviousBit("GNT/REQ/");

                       }
                        gnthigh=false;
                    }
                    else if(Transaction=="Write")
                    {
                       MainWindow::WriteTransaction(master,masterTarget);
                       if(!gnthigh)
                       {
                           master->SetPreviousBit("GNT/REQ/");
                           gnthigh=false;
                       }
                        gnthigh=false;
                    }
                }
                // condition to append to main bus when the transaction ends and i don't enter
                //the condition of READ and WRITE
                else if (mainBus->GetFrameBit()=='1' && mainBus->GetIRDYBit()=='1'&& endTransaction)
                {
                    endTransaction=false;
                    mainBus->SetPreviousBit("Frame/AD/CBE/IRDY/TRDY/DEVSEL/Reset/");
                }
            }


        }
        else // at postive edge
        {
            if(mainCounter==1)
            {
                DeviceA->SetPreviousBit("GNT/REQ/");
                DeviceB->SetPreviousBit("GNT/REQ/");
                DeviceC->SetPreviousBit("GNT/REQ/");
                DeviceD->SetPreviousBit("GNT/REQ/");
                mainBus->SetPreviousBit("Frame/AD/CBE/IRDY/TRDY/DEVSEL/Reset/");
            }
            else
            {
                master->SetPreviousBit("GNT/REQ/");
                for(int i=0;i<nonActive.size();i++)
                {
                    nonActive[i]->SetPreviousBit("GNT/REQ/");
                }
                mainBus->SetPreviousBit("Frame/AD/CBE/IRDY/TRDY/DEVSEL/Reset/");
            }

        }



    }


}


void MainWindow::ReadTransaction(DEVICE *Initiator, DEVICE *Target)
{
            if(mainBus->GetFrameBit()=='1' && beginTransaction) // begin transaction
            {
                masterControl->decrementTrans();
                dataCounter=0;
                mainBus->SetFrame("0");
                mainBus->SetAD("/1");
                mainBus->Setdata("/"+Target->GetDeviceName());
                mainBus->SetCBE("/1");
                mainBus->SetControl_Byte("/Read");
                mainBus->SetPreviousBit("TRDY/IRDY/DEVSEL/Reset/");
                beginTransaction=false;
            }
            // to detrmine READ OR WRITE
            // the SET IRDY low
            else if(mainBus->GetFrameBit()=='0' && mainBus->GetControl_ByteBit()=="Read")
            {
                mainBus->SetAD("/1");
                mainBus->Setdata("/x");
                mainBus->SetIRDY("0");
                mainBus->SetDEVSEL("0");
                mainBus->SetCBE("/1");
                mainBus->SetControl_Byte("/x");
                mainBus->SetPreviousBit("Frame/TRDY/Reset/");
            }
            // to make target ready and begin transaction since READ transaction and
            // the transacton will begin when both TRDY and IRDY are low
            //Target put the data on the dataline
            else if(mainBus->GetFrameBit()=='0' && mainBus->GetDataBit()=="x" && mainBus->GetIRDYBit()=='0')
            {
                mainBus->SetAD("/1");
                mainBus->Setdata("/"+Target->GetMemoryWord(dataCounter));
                mainBus->SetTRDY("0");
                Initiator->SetMemoryWord(Target->GetMemoryWord(dataCounter),dataCounter);
                numberOfTransfers--;
                dataCounter++;
                if(numberOfTransfers==0)
                {
                   mainBus->SetFrame("1");
                   mainBus->SetPreviousBit("CBE/IRDY/DEVSEL/Reset/");
                }
                else
                   mainBus->SetPreviousBit("Frame/CBE/IRDY/DEVSEL/Reset/");
            }
            // if multiple data transfers
            // and if number of transfer reach zero make Frame high
            else if(mainBus->GetFrameBit()=='0' && mainBus->GetIRDYBit()=='0' && mainBus->GetTRDYBit()=='0' && numberOfTransfers!=0)
            {
                 mainBus->SetAD("/1");
                 mainBus->Setdata("/"+Target->GetMemoryWord(dataCounter));
                 Initiator->SetMemoryWord(Target->GetMemoryWord(dataCounter),dataCounter);
                 numberOfTransfers--;
                 dataCounter++;
                 if(numberOfTransfers==0)
                 {
                    mainBus->SetFrame("1");
                    mainBus->SetPreviousBit("CBE/IRDY/TRDY/DEVSEL/Reset/");
                 }
                 else
                    mainBus->SetPreviousBit("Frame/CBE/IRDY/TRDY/DEVSEL/Reset/");

            }
            // finish the transaction
            else if(mainBus->GetFrameBit()=='1' && mainBus->GetIRDYBit()=='0' && mainBus->GetTRDYBit()=='0')
            {
                mainBus->SetAD("/1");
                mainBus->Setdata("/x");
                mainBus->SetIRDY("1");
                mainBus->SetTRDY("1");
                mainBus->SetDEVSEL("1");
                mainBus->SetPreviousBit("Frame/CBE/Reset/");
                endTransaction=true;
                beginTransaction=true;
            }
    return;
}

void MainWindow::WriteTransaction(DEVICE *Initiator, DEVICE *Target){

int transNumber=0;
QString data="";
            if(mainBus->GetFrameBit()=='1' && beginTransaction) // begin transaction
            {

                    if(masterControl->get_numOfTrans()==2)
                        transNumber=0;
                    else if (masterControl->get_numOfTrans()==1)
                        transNumber=1;
                masterControl->decrementTrans();
                dataCounter=0;
                mainBus->SetFrame("0");
                mainBus->SetAD("/1");
                mainBus->Setdata("/"+Target->GetDeviceName());
                mainBus->SetCBE("/1");
                mainBus->SetControl_Byte("/Write");
                mainBus->SetPreviousBit("TRDY/IRDY/DEVSEL/Reset/");
                beginTransaction=false;
            }
            // to detrmine READ OR WRITE
            // the SET IRDY low
            else if(mainBus->GetFrameBit()=='0' && mainBus->GetControl_ByteBit()=="Write")
            {
                data=Initiator->GetMemoryByteEnable(dataCounter,masterControl->get_ByteEnable(transNumber,dataCounter));
                mainBus->SetAD("/1");
                mainBus->Setdata("/"+data);
                mainBus->SetIRDY("0");
                mainBus->SetTRDY("0");
                mainBus->SetDEVSEL("0");
                mainBus->SetCBE("/1");
                mainBus->SetControl_Byte("/"+masterControl->get_ByteEnable(transNumber,dataCounter));

                Target->SetMemoryByteEnable(data,dataCounter,masterControl->get_ByteEnable(transNumber,dataCounter));
                numberOfTransfers--;
                dataCounter++;
                if(numberOfTransfers==0)
                {
                   mainBus->SetFrame("1");
                   mainBus->SetPreviousBit("Reset/");
                }
                else
                   mainBus->SetPreviousBit("Frame/Reset/");
            }
            // if multiple data transfers
            // and if number of transfer reach zero make Frame high
            else if(mainBus->GetFrameBit()=='0' && mainBus->GetIRDYBit()=='0' && mainBus->GetTRDYBit()=='0' && numberOfTransfers!=0)
            {
                 data=Initiator->GetMemoryByteEnable(dataCounter,masterControl->get_ByteEnable(transNumber,dataCounter));
                 mainBus->SetAD("/1");
                 mainBus->Setdata("/"+data);
                 Target->SetMemoryByteEnable(data,dataCounter,masterControl->get_ByteEnable(transNumber,dataCounter));
                 mainBus->SetCBE("/1");
                 mainBus->SetControl_Byte("/"+masterControl->get_ByteEnable(transNumber,dataCounter));
                 numberOfTransfers--;
                 dataCounter++;
                 if(numberOfTransfers==0)
                 {
                    mainBus->SetFrame("1");
                    mainBus->SetPreviousBit("IRDY/TRDY/DEVSEL/Reset/");
                 }
                 else
                    mainBus->SetPreviousBit("Frame/IRDY/TRDY/DEVSEL/Reset/");

            }
            // finish the transaction
            else if(mainBus->GetFrameBit()=='1' && mainBus->GetIRDYBit()=='0' && mainBus->GetTRDYBit()=='0')
            {
                mainBus->SetAD("/1");
                mainBus->Setdata("/x");
                mainBus->SetIRDY("1");
                mainBus->SetTRDY("1");
                mainBus->SetDEVSEL("1");
                mainBus->SetCBE("/1");
                mainBus->SetControl_Byte("/x");
                mainBus->SetPreviousBit("Frame/Reset/");
                endTransaction=true;
                beginTransaction=true;
            }


    return ;
}


void MainWindow::on_DevA_spinBox_editingFinished()
{
    if(ui->DevA_spinBox->value() <=2){

        SubWindow = new subWindow(this,ui->DevA_spinBox->value(),"DEVICE A",devA_main,devB_main,devC_main,devD_main,
                                   DeviceA,DeviceB,DeviceC,DeviceD);
        SubWindow->setModal(true);
        SubWindow->setWindowTitle("DEVICE A");
        if(ui->DevA_spinBox->value() != 0){
            devA_main->set_numOfTrans(ui->DevA_spinBox->value());
            ui->DevA_spinBox->blockSignals(true);
            ui->DevA_spinBox->setEnabled(false);
            SubWindow->exec();
            ui->DevA_spinBox->blockSignals(false);
        }
    }
    else{
         ui->DevA_spinBox->blockSignals(true);
        QMessageBox::warning(this,"Error","Number of Transactions can't be more than 2");
         ui->DevA_spinBox->blockSignals(false);
    }
}

void MainWindow::on_DevB_spinBox_editingFinished()
{
    if(ui->DevB_spinBox->value()<=2){
        SubWindow = new subWindow(this,ui->DevB_spinBox->value(),"DEVICE B",devA_main,devB_main,devC_main,devD_main,
                                   DeviceA,DeviceB,DeviceC,DeviceD);
        SubWindow->setModal(true);
        SubWindow->setWindowTitle("DEVICE B");
        if(ui->DevB_spinBox->value() != 0){
            ui->DevB_spinBox->blockSignals(true);
            ui->DevB_spinBox->setEnabled(false);
            devB_main->set_numOfTrans(ui->DevB_spinBox->value());
            SubWindow->exec();
            ui->DevB_spinBox->blockSignals(false);
        }
    }
    else{
         ui->DevB_spinBox->blockSignals(true);
        QMessageBox::warning(this,"Error","Number of Transactions can't be more than 2");
         ui->DevB_spinBox->blockSignals(false);
    }
}

void MainWindow::on_DevC_spinBox_editingFinished()
{
    if(ui->DevC_spinBox->value()<=2){
        SubWindow = new subWindow(this,ui->DevC_spinBox->value(),"DEVICE C",devA_main,devB_main,devC_main,devD_main,
                                  DeviceA,DeviceB,DeviceC,DeviceD );
        SubWindow->setModal(true);
        SubWindow->setWindowTitle("DEVICE C");
        if(ui->DevC_spinBox->value() != 0){
            ui->DevC_spinBox->blockSignals(true);
            ui->DevC_spinBox->setEnabled(false);
            devC_main->set_numOfTrans(ui->DevC_spinBox->value());
            SubWindow->exec();
            ui->DevC_spinBox->blockSignals(false);
        }
    }
    else{
        ui->DevC_spinBox->blockSignals(true);
        QMessageBox::warning(this,"Error","Number of Transactions can't be more than 2");
         ui->DevC_spinBox->blockSignals(false);
    }
}

void MainWindow::on_DevD_spinBox_editingFinished()
{
    if(ui->DevD_spinBox->value()<=2){
        SubWindow = new subWindow(this,ui->DevD_spinBox->value(),"DEVICE D",devA_main,devB_main,devC_main,devD_main,
                                  DeviceA,DeviceB,DeviceC,DeviceD);
        SubWindow->setModal(true);
        SubWindow->setWindowTitle("DEVICE D");
        if(ui->DevD_spinBox->value() != 0){
            ui->DevD_spinBox->blockSignals(true);
            ui->DevD_spinBox->setEnabled(false);
            devD_main->set_numOfTrans(ui->DevD_spinBox->value());
            SubWindow->exec();
            ui->DevD_spinBox->blockSignals(false);
        }
    }
    else{
         ui->DevD_spinBox->blockSignals(true);
        QMessageBox::warning(this,"Error","Number of Transactions can't be more than 2");
         ui->DevD_spinBox->blockSignals(false);
    }
}



void MainWindow::on_DevA_ByteIndex_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Byte 1"){
         ui->DevA_Byte1->setEnabled(true);
         ui->DevA_Byte2->setEnabled(false);
         ui->DevA_Byte3->setEnabled(false);
         ui->DevA_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 2"){
        ui->DevA_Byte1->setEnabled(false);
        ui->DevA_Byte2->setEnabled(true);
        ui->DevA_Byte3->setEnabled(false);
        ui->DevA_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 3"){
        ui->DevA_Byte1->setEnabled(false);
        ui->DevA_Byte2->setEnabled(false);
        ui->DevA_Byte3->setEnabled(true);
        ui->DevA_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 4")
    {
        ui->DevA_Byte1->setEnabled(false);
        ui->DevA_Byte2->setEnabled(false);
        ui->DevA_Byte3->setEnabled(false);
        ui->DevA_Byte4->setEnabled(true);
    }
    else {
        ui->DevA_Byte1->setEnabled(true);
        ui->DevA_Byte2->setEnabled(true);
        ui->DevA_Byte3->setEnabled(true);
        ui->DevA_Byte4->setEnabled(true);
    }
}

void MainWindow::on_DevB_ByteIndex_currentTextChanged(const QString &arg1)
{

    if(arg1 == "Byte 1"){
         ui->DevB_Byte1->setEnabled(true);
         ui->DevB_Byte2->setEnabled(false);
         ui->DevB_Byte3->setEnabled(false);
         ui->DevB_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 2"){
        ui->DevB_Byte1->setEnabled(false);
        ui->DevB_Byte2->setEnabled(true);
        ui->DevB_Byte3->setEnabled(false);
        ui->DevB_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 3"){
        ui->DevB_Byte1->setEnabled(false);
        ui->DevB_Byte2->setEnabled(false);
        ui->DevB_Byte3->setEnabled(true);
        ui->DevB_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 4")
    {
        ui->DevB_Byte1->setEnabled(false);
        ui->DevB_Byte2->setEnabled(false);
        ui->DevB_Byte3->setEnabled(false);
        ui->DevB_Byte4->setEnabled(true);
    }
    else {
        ui->DevB_Byte1->setEnabled(true);
        ui->DevB_Byte2->setEnabled(true);
        ui->DevB_Byte3->setEnabled(true);
        ui->DevB_Byte4->setEnabled(true);
    }
}

void MainWindow::on_DevC_ByteIndex_currentTextChanged(const QString &arg1)
{

    if(arg1 == "Byte 1"){
         ui->DevC_Byte1->setEnabled(true);
         ui->DevC_Byte2->setEnabled(false);
         ui->DevC_Byte3->setEnabled(false);
         ui->DevC_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 2"){
        ui->DevC_Byte1->setEnabled(false);
        ui->DevC_Byte2->setEnabled(true);
        ui->DevC_Byte3->setEnabled(false);
        ui->DevC_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 3"){
        ui->DevC_Byte1->setEnabled(false);
        ui->DevC_Byte2->setEnabled(false);
        ui->DevC_Byte3->setEnabled(true);
        ui->DevC_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 4")
    {
        ui->DevC_Byte1->setEnabled(false);
        ui->DevC_Byte2->setEnabled(false);
        ui->DevC_Byte3->setEnabled(false);
        ui->DevC_Byte4->setEnabled(true);
    }
    else {
        ui->DevC_Byte1->setEnabled(true);
        ui->DevC_Byte2->setEnabled(true);
        ui->DevC_Byte3->setEnabled(true);
        ui->DevC_Byte4->setEnabled(true);
    }
}

void MainWindow::on_DevD_ByteIndex_currentTextChanged(const QString &arg1)
{

    if(arg1 == "Byte 1"){
         ui->DevD_Byte1->setEnabled(true);
         ui->DevD_Byte2->setEnabled(false);
         ui->DevD_Byte3->setEnabled(false);
         ui->DevD_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 2"){
        ui->DevD_Byte1->setEnabled(false);
        ui->DevD_Byte2->setEnabled(true);
        ui->DevD_Byte3->setEnabled(false);
        ui->DevD_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 3"){
        ui->DevD_Byte1->setEnabled(false);
        ui->DevD_Byte2->setEnabled(false);
        ui->DevD_Byte3->setEnabled(true);
        ui->DevD_Byte4->setEnabled(false);
    }
    else if(arg1=="Byte 4")
    {
        ui->DevD_Byte1->setEnabled(false);
        ui->DevD_Byte2->setEnabled(false);
        ui->DevD_Byte3->setEnabled(false);
        ui->DevD_Byte4->setEnabled(true);
    }
    else {
        ui->DevD_Byte1->setEnabled(true);
        ui->DevD_Byte2->setEnabled(true);
        ui->DevD_Byte3->setEnabled(true);
        ui->DevD_Byte4->setEnabled(true);
    }
}

void MainWindow::on_Submit_clicked(bool checked)
{



    senarioFlag=true;
    if(ui->DevA_InitiatorRadio->isChecked())
    {
       ui->DevA_InitiatorRadio->setChecked(false);
       ui->DevA_IdleRadio->setChecked(true);
       MastersSelect.append(DeviceA);
       MastersControl.append(devA_main);
       delay.append(ui->Delay->value());
    }

    if(ui->DevB_InitiatorRadio->isChecked())
    {
       ui->DevB_InitiatorRadio->setChecked(false);
       ui->DevB_IdleRadio->setChecked(true);
       MastersSelect.append(DeviceB);
       MastersControl.append(devB_main);
       delay.append(ui->Delay->value());
    }
    if(ui->DevC_InitiatorRadio->isChecked())
    {
       ui->DevC_InitiatorRadio->setChecked(false);
       ui->DevC_IdleRadio->setChecked(true);
       MastersSelect.append(DeviceC);
       MastersControl.append(devC_main);
       delay.append(ui->Delay->value());
    }
    if(ui->DevD_InitiatorRadio->isChecked())
    {
       ui->DevD_InitiatorRadio->setChecked(false);
       ui->DevD_IdleRadio->setChecked(true);
       MastersSelect.append(DeviceD);
       MastersControl.append(devD_main);
       delay.append(ui->Delay->value());
    }




    for(int i=0;i<10;i++){
        if(i == ui->DevA_RowIndex->currentIndex()){

            if(ui->DevA_ByteIndex->currentIndex() ==1)
                DeviceA->SetMemoryByte(ui->DevA_Byte1->text(),i,0);
            else if(ui->DevA_ByteIndex->currentIndex() == 2)
                DeviceA->SetMemoryByte(ui->DevA_Byte2->text(),i,1);
            else if(ui->DevA_ByteIndex->currentIndex() == 3)
                DeviceA->SetMemoryByte(ui->DevA_Byte3->text(),i,2);
            else if(ui->DevA_ByteIndex->currentIndex() == 4)
                DeviceA->SetMemoryByte(ui->DevA_Byte4->text(),i,3);

        }
        if(i == ui->DevB_RowIndex->currentIndex()){

            if(ui->DevB_ByteIndex->currentIndex() ==1)
                DeviceB->SetMemoryByte(ui->DevB_Byte1->text(),i,0);
            else if(ui->DevB_ByteIndex->currentIndex() == 2)
                DeviceB->SetMemoryByte(ui->DevB_Byte2->text(),i,1);
            else if(ui->DevB_ByteIndex->currentIndex() == 3)
                DeviceB->SetMemoryByte(ui->DevB_Byte3->text(),i,2);
            else if(ui->DevB_ByteIndex->currentIndex() == 4)
                DeviceB->SetMemoryByte(ui->DevB_Byte4->text(),i,3);
        }
        if(i == ui->DevC_RowIndex->currentIndex()){
            if(ui->DevC_ByteIndex->currentIndex() ==1)
                DeviceC->SetMemoryByte(ui->DevC_Byte1->text(),i,0);
            else if(ui->DevC_ByteIndex->currentIndex() == 2)
                DeviceC->SetMemoryByte(ui->DevC_Byte2->text(),i,1);
            else if(ui->DevC_ByteIndex->currentIndex() == 3)
                DeviceC->SetMemoryByte(ui->DevC_Byte3->text(),i,2);
            else if(ui->DevC_ByteIndex->currentIndex() == 4)
                DeviceC->SetMemoryByte(ui->DevC_Byte4->text(),i,3);
        }
        if(i == ui->DevD_RowIndex->currentIndex()){
            if(ui->DevD_ByteIndex->currentIndex() ==1)
                DeviceD->SetMemoryByte(ui->DevD_Byte1->text(),i,0);
            else if(ui->DevD_ByteIndex->currentIndex() == 2)
                DeviceD->SetMemoryByte(ui->DevD_Byte2->text(),i,1);
            else if(ui->DevD_ByteIndex->currentIndex() == 3)
                DeviceD->SetMemoryByte(ui->DevD_Byte3->text(),i,2);
            else if(ui->DevD_ByteIndex->currentIndex() == 4)
                DeviceD->SetMemoryByte(ui->DevD_Byte4->text(),i,3);
        }
    }

}


void MainWindow::on_DevA_RowIndex_currentIndexChanged(const QString &arg1)
{
    for(int i=0;i<10;i++){
        if(i == ui->DevA_RowIndex->currentIndex()){

            ui->DevA_Byte1->setText(DeviceA->GetMemoryByte(i,0));
            ui->DevA_Byte2->setText(DeviceA->GetMemoryByte(i,1));
            ui->DevA_Byte3->setText(DeviceA->GetMemoryByte(i,2));
            ui->DevA_Byte4->setText(DeviceA->GetMemoryByte(i,3));

        }
    }
}

void MainWindow::on_DevB_RowIndex_currentIndexChanged(const QString &arg1)
{
    for(int i=0;i<10;i++){
        if(i == ui->DevB_RowIndex->currentIndex()){

            ui->DevB_Byte1->setText(DeviceB->GetMemoryByte(i,0));
            ui->DevB_Byte2->setText(DeviceB->GetMemoryByte(i,1));
            ui->DevB_Byte3->setText(DeviceB->GetMemoryByte(i,2));
            ui->DevB_Byte4->setText(DeviceB->GetMemoryByte(i,3));

        }
    }
}

void MainWindow::on_DevC_RowIndex_currentIndexChanged(const QString &arg1)
{
    for(int i=0;i<10;i++){
        if(i == ui->DevC_RowIndex->currentIndex()){

            ui->DevC_Byte1->setText(DeviceC->GetMemoryByte(i,0));
            ui->DevC_Byte2->setText(DeviceC->GetMemoryByte(i,1));
            ui->DevC_Byte3->setText(DeviceC->GetMemoryByte(i,2));
            ui->DevC_Byte4->setText(DeviceC->GetMemoryByte(i,3));

        }
    }
}

void MainWindow::on_DevD_RowIndex_currentIndexChanged(const QString &arg1)
{
    for(int i=0;i<10;i++){
        if(i == ui->DevD_RowIndex->currentIndex()){

            ui->DevD_Byte1->setText(DeviceD->GetMemoryByte(i,0));
            ui->DevD_Byte2->setText(DeviceD->GetMemoryByte(i,1));
            ui->DevD_Byte3->setText(DeviceD->GetMemoryByte(i,2));
            ui->DevD_Byte4->setText(DeviceD->GetMemoryByte(i,3));

        }
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index==0)
        arbiterMoodIndex=0;
    else
        arbiterMoodIndex=1;
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "Performing application reboot...";
     qApp->exit( MainWindow::EXIT_CODE_REBOOT );
}
