#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serialport_Constructor();
    modbus_tcp_dv02_Constructor();
    modbus_tcp_dv03_Constructor();
    modbus_rtu_dv04_Constructor();
    device_action_Constructor();

    file_action_Constructor();
    //ui->User_Groupbox->hide();
    //ui->Data_Groupbox->hide();
    //ui->plot->setMaximumHeight(900);
    change_unit_action_Constructor();
    graph_Constructor();
    file_is_change_Constructor();

    disconnect_button_Constructor();

    //StartTime = new QTimer(this); //ตามเวลาที่เลือก
    RunTime   = new QTimer(this);
    connect(RunTime, &QTimer::timeout,
            this, &MainWindow::tiktok);

    ui->END_BTN->setEnabled(false);

    ui->PigmentWeight_LE->setValidator(new QDoubleValidator(0, 99999, 5, this));
    ui->TotalWeight_LE->setValidator(new QDoubleValidator(0, 99999, 5, this));
    ui->FilterScreenSize_LE->setValidator(new QDoubleValidator(0, 99999, 5, this));

    connect(ui->actionAll,&QAction::triggered,
            this,&MainWindow::Hide_And_Show_All_Graph);
    connect(ui->actionP1,&QAction::triggered,
            this,&MainWindow::Hide_And_Show_P1_Graph);
    connect(ui->actionP2,&QAction::triggered,
            this,&MainWindow::Hide_And_Show_P2_Graph);
    connect(ui->actionT1,&QAction::triggered,
            this,&MainWindow::Hide_And_Show_T1_Graph);
    connect(ui->actionT2,&QAction::triggered,
            this,&MainWindow::Hide_And_Show_T2_Graph);
    connect(ui->actionExt,&QAction::triggered,
            this,&MainWindow::Hide_And_Show_Ext_Graph);
    connect(ui->actionGp,&QAction::triggered,
            this,&MainWindow::Hide_And_Show_Gp_Graph);
    connect(ui->actionA1,&QAction::triggered,
            this,&MainWindow::Hide_And_Show_A1_Graph);
    connect(ui->actionA2,&QAction::triggered,
            this,&MainWindow::Hide_And_Show_A2_Graph);

    ui->actionP1->setChecked(true);
    ui->actionP2->setChecked(true);
    ui->actionT1->setChecked(true);
    ui->actionT2->setChecked(true);
    ui->actionExt->setChecked(true);
    ui->actionGp->setChecked(true);
    ui->actionA1->setChecked(true);
    ui->actionA2->setChecked(true);

    ui->plot->setInteractions(QCP::iRangeDrag |QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);

    connect(ui->plot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));
    connect(ui->plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    ignore_Close = false;

    checker.isFit_click  = true;
    checker.isZoom_click = false;
}



MainWindow::~MainWindow()
{
    delete ui;
}

/******************************************************************************************************************/
void MainWindow::device01_connect_to_dev()
{
    serial.setPortName(m_serialport.getComPort());
    serial.setDataBits(static_cast<QSerialPort::DataBits>(m_serialport.getDataBits().toInt()));
    serial.setStopBits(static_cast<QSerialPort::StopBits>(m_serialport.getStopBits().toInt()));
    serial.setParity(static_cast<QSerialPort::Parity>(m_serialport.getParity().toInt()));
    serial.setBaudRate(static_cast<QSerialPort::BaudRate>(m_serialport.getBuadRate().toInt()));
    serial.setFlowControl(static_cast<QSerialPort::FlowControl>(m_serialport.getFlowControl().toInt()));
    if(serial.open(QIODevice::ReadWrite))
    {
        //ui->textEdit->append("Open Port Success\r\n");
        qDebug()<<"Open Port Success\r\n";
        statusBar()->showMessage(tr("Device01 Connected"), 2000);
        //TestSerial->start(100000);
        ui->SerialPort_BTN->setEnabled(true);
        ui->SerialPort_BTN->setChecked(true);
    }
    else{
        //ui->textEdit->append("Unable to open Com Port");
         qDebug()<<"Open Port NotSuccess\r\n";
         ui->SerialPort_BTN->setEnabled(false);
         ui->SerialPort_BTN->setChecked(false);
    }
}

void MainWindow::device01_disconnect_from_dev()
{
    serial.close();
    ui->SerialPort_BTN->setEnabled(false);
    ui->SerialPort_BTN->setChecked(false);
}

void MainWindow::device01_read()
{
    QByteArray data = serial.readAll();
    //ui->plainTextEdit->insertPlainText(QString(data));
    if(data!="")
    {
        QString code = QString(data);
        QStringList item = code.split("");
        int A;
        int B;
        int C;
        int D;
        int E;
        int F;
        int G;
        int H;
        int I;
        int sharp;
        for(int i =0 ;i<item.size();i++)
        {
            if(item.at(i) == 'A')
            {
                A = i;
            }

            else if (item.at(i) == 'B')
            {
                B = i;
            }

            else if (item.at(i) == 'C')
            {
                C = i;
            }
            else if (item.at(i) == 'D')
            {
                D = i;
            }
            else if (item.at(i) == 'E')
            {
                E = i;
            }
            else if (item.at(i) == 'F')
            {
                F = i;
            }
            else if (item.at(i) == 'G')
            {
                G = i;
            }
            else if (item.at(i) == 'H')
            {
                H = i;
            }
            else if (item.at(i) == 'I')
            {
                I = i;
            }
            else if (item.at(i) == '#')
            {
                sharp = i;
            }
        }
        icount++;

        P2 = SplitCode(item,&A,&B).toDouble()/10.0;
        P1 = SplitCode(item,&B,&C).toDouble()/10.0;
        T2 = SplitCode(item,&C,&D).toUInt();
        T1 = SplitCode(item,&D,&E).toUInt();

        qDebug() << "AFTER A = "<<SplitCode(item,&A,&B).toDouble()/10;
        qDebug() << "AFTER B = "<<SplitCode(item,&B,&C).toDouble()/10;
        qDebug() << "AFTER C = "<<SplitCode(item,&C,&D).toUInt();
        qDebug() << "AFTER D = "<<SplitCode(item,&D,&E).toUInt();
        qDebug() << "AFTER E = "<<SplitCode(item,&E,&F).toDouble()/10;
        qDebug() << "AFTER F = "<<SplitCode(item,&F,&G).toDouble()/10;
        qDebug() << "AFTER G = "<<SplitCode(item,&G,&H).toUInt();
        qDebug() << "AFTER H = "<<SplitCode(item,&H,&I).toDouble()/10;
        qDebug() << "AFTER I = "<<SplitCode(item,&I,&sharp).toDouble()/10;
    }


    v_y1.push_back(P2); //เอา Pstart = v_y1[0],Pmax เอาทุก Vector มาเรียงหาค่า max
    double P2_max = *max_element(v_y1.begin(), v_y1.end());
    double P2_min = *min_element(v_y1.begin(), v_y1.end());
    v_y2.push_back(T2); //เอา Tstart = v_y2[0],Tend เอาค่าสุดท้าย,Tmax and Tmin เอา vector มาเรียง
    double T2_max = *max_element(v_y2.begin(), v_y2.end());
    double T2_min = *min_element(v_y2.begin(), v_y2.end());
    v_y3.push_back(T1); //เอา Tstart = v_y3[0],Tend เอาค่าสุดท้าย
    double T1_max = *max_element(v_y3.begin(), v_y3.end());
    double T1_min = *min_element(v_y3.begin(), v_y3.end());

    v_y4.push_back(P1);
    double P1_max = *max_element(v_y4.begin(), v_y4.end());
    double P1_min = *min_element(v_y4.begin(), v_y4.end());

    v_maxValue.push_back(P2_max);
    v_minValue.push_back(P2_min);

    v_maxValue.push_back(T2_max);
    v_minValue.push_back(T2_min);

    v_maxValue.push_back(T1_max);
    v_minValue.push_back(T1_min);

    v_maxValue.push_back(P1_max);
    v_minValue.push_back(P1_min);

    range_max = *max_element(v_maxValue.begin(), v_maxValue.end());
    range_min = *min_element(v_minValue.begin(), v_minValue.end());

    QString Pstart = QString::number(v_y1.at(0));
    QString Pmax = QString::number(P2_max);
    QString DelP = QString::number(P2_max-v_y1.at(0));
    QString FPV = QString::number((P2_max-v_y1.at(0))/ui->PigmentWeight_LE->text().toDouble());
    //QString Pend = QString::number(v_y1.back());
    ui->PStart_LE->setText(Pstart);
    ui->PMax_LE->setText(Pmax);
    ui->DelP_LE->setText(DelP);
    ui->FPV_LE->setText(FPV);

    QString Pstart_PumpInletPressure = QString::number(v_y4.at(0));
    QString Pend_PumpInletPressure   = QString::number(v_y4.back());

    ui->PressStartPumpInlet_LE->setText(Pstart_PumpInletPressure);
    ui->PressEndPumpInlet_LE->setText(Pend_PumpInletPressure);

    QString Tstart_tempAtscreen = QString::number(v_y2.at(0));
    QString Tend_tempAtscreen = QString::number(v_y2.back());
    QString Tmax_tempAtscreen = QString::number(T2_max);
    QString Tmin_tempAtscreen = QString::number(T2_min);
    ui->TStart_LE->setText(Tstart_tempAtscreen);
    ui->TEnd_LE->setText(Tend_tempAtscreen);
    ui->TMax_LE->setText(Tmax_tempAtscreen);
    ui->TMin_LE->setText(Tmin_tempAtscreen);

    QString Tstart_PumpInletTemp = QString::number(v_y3.at(0));
    QString Tend_PumpInletTemp = QString::number(v_y3.back());
    ui->TempStartPumpInlet_LE->setText(Tstart_PumpInletTemp);
    ui->TempEndPumpInlet_LE->setText(Tend_PumpInletTemp);

    /*Feed rate*/
    /*double feed_rate = ค่าที่เข้ามา
     * double showNum;
     * if(ui->actionCC_Min->isChecked())
     * {
     *       showNum = feed_rate*scale.getCc_min_scale().toDouble();
     * }
     * else
     * {
     *      showNum = feed_rate;
     * }
     *
    */
    /*End Feed rate*/
    /*P2*/
    qv_x1.append(sec);
    qv_y1.append(v_y1.back());
    ui->plot->graph(1)->setData(qv_x1,qv_y1);

    /*T2*/
    qv_x2.append(sec);
    qv_y2.append(v_y2.back());
    ui->plot->graph(3)->setData(qv_x2,qv_y2);

    /*T1*/
    qv_x3.append(sec);
    qv_y3.append(v_y3.back());
    ui->plot->graph(2)->setData(qv_x3,qv_y3);

    /*P1*/
    qv_x4.append(sec);
    qv_y4.append(v_y4.back());
    ui->plot->graph(0)->setData(qv_x4,qv_y4);

    if(checker.isFit_click==true)
    {
        ui->plot->xAxis->setRange(0,sec+5);
        ui->plot->yAxis->setRange(range_min-25,range_max+25);
        ui->plot->yAxis2->setRange(range_min-25,range_max+25);
        ui->plot->replot();
    }
    else
    {
        ui->plot->replot();
    }


    //qDebug()<<P2_max;

    /*Test Graph*/
     //qv_x1.append(sec);
     //qv_y1.append(9);
     //ui->plot->graph(0)->setData(qv_x1,qv_y1);
     //ui->plot->xAxis->setRange(0,sec);
     //ui->plot->yAxis->setRange(0,10);
     //ui->plot->replot();
    /*Test Graph*/

    /*QString code = QString(data);
    QStringList item = code.split("");
    int A;
    int B;
    int C;
    int D;
    int E;
    int F;
    int G;
    int H;
    int I;
    int sharp;
    for(int i =0 ;i<item.size();i++)
    {
        if(item.at(i) == 'A')
        {
            A = i;
        }

        else if (item.at(i) == 'B')
        {
            B = i;
        }

        else if (item.at(i) == 'C')
        {
            C = i;
        }
        else if (item.at(i) == 'D')
        {
            D = i;
        }
        else if (item.at(i) == 'E')
        {
            E = i;
        }
        else if (item.at(i) == 'F')
        {
            F = i;
        }
        else if (item.at(i) == 'G')
        {
            G = i;
        }
        else if (item.at(i) == 'H')
        {
            H = i;
        }
        else if (item.at(i) == 'I')
        {
            I = i;
        }
        else if (item.at(i) == '#')
        {
            sharp = i;
        }
    }
    qDebug() << "AFTER A = "<<SplitCode(item,&A,&B).toDouble()/10;
    qDebug() << "AFTER B = "<<SplitCode(item,&B,&C).toDouble()/10;
    qDebug() << "AFTER C = "<<SplitCode(item,&C,&D).toUInt();
    qDebug() << "AFTER D = "<<SplitCode(item,&D,&E).toUInt();
    qDebug() << "AFTER E = "<<SplitCode(item,&E,&F).toDouble()/10;
    qDebug() << "AFTER F = "<<SplitCode(item,&F,&G).toDouble()/10;
    qDebug() << "AFTER G = "<<SplitCode(item,&G,&H).toUInt();
    qDebug() << "AFTER H = "<<SplitCode(item,&H,&I).toDouble()/10;
    qDebug() << "AFTER I = "<<SplitCode(item,&I,&sharp).toDouble()/10;*/


}

void MainWindow::device01_write()
{
    serial.write("#A");
    device01_read();
    //qDebug() << QString(TestSerial);
}


/******************************************************************************************************************/
void MainWindow::device02_connect_to_dev()
{

    device02_mbTCP.IP = m_tcp.getIPv4();                                //device02_dialog->IPV4_Selected();
    device02_mbTCP.port = m_tcp.getPort().toInt();                      //device02_dialog->Port_Selected().toInt();
    device02_mbTCP.set_slave(m_tcp.getSlave().toInt());                 //device02_dialog->Slave_Selected().toInt()

    device02_mbTCP.connect();
}

void MainWindow::device02_disconnect_from_dev()
{
    device02_mbTCP.disconnect();
}

void MainWindow::device02_read_regs()
{
    int addr = m_tcp.getReg().toInt();                                  //device02_dialog->Reg_Selected().toInt();
    int count = m_tcp.getCount().toInt();                               //device02_dialog->Count_Selected().toInt();

    if(count > MODBUS_MAX_READ_REGISTERS)
    {
        QMessageBox::warning(this,"Error Register",QString("Error count reg is: %1 Max count reg is: %2").arg(count).arg(MODBUS_MAX_READ_REGISTERS));
        return;
    }
    if(count <= 0)
    {
        QMessageBox::warning(this,"Error Register",QString("Error count reg is: %1").arg(count));
        return;
    }
    device02_mbTCP.read_regs(addr,count,rd_buf_device02);
}

void MainWindow::device02_response_to_read_regs(int status)
{
    int i;

    if(status<=0)
        return;
    for(i = 0; i < status; i++)
    {
        if(i==0)
        {
            //ui->lcdNumber->display(rd_buf_device02[i]);//แสดงบน ui
        }
        else if(i==1)
        {
            //ui->lcdNumber_2->display(rd_buf_device02[i]);//แสดงบน ui
        }
        else if(i==2)
        {
            //ui->lcdNumber_3->display(rd_buf_device02[i]);//แสดงบน ui
        }
        //ui->log_plain_text_edit->appendPlainText(QString("reg[%1] == %2").arg(i).arg(rd_buf_device02[i]));
    }
}

void MainWindow::device02_process_error(QModBus::ModBusError error)
{
    timer->stop();//เพื่อไม่ให้ QMessageBox เด้งทุกๆวินาทีตอน error
    switch (error)
    {

        case QModBus::NoConnectionError:
        case QModBus::CreateError:
        case QModBus::ConnectionError:
        {
            QMessageBox::critical(this,"ERROR","Connection Error or Create Error");
            ui->actionMODBUS_TCP->setChecked(false);
            break;
        }


        case QModBus::ReadRegsError:
        {
            QMessageBox::critical(this,"ERROR","Read Register Error");
            break;
        }


        case QModBus::WriteRegError:
        {
            QMessageBox::critical(this,"ERROR","Write Register Error");
            break;
        }


        default:
            break;
    }

}

void MainWindow::device02_change_status()
{
    if(device02_mbTCP.is_connected())
    {
        QMessageBox::information(this,"Device2 Connected","Device2 TCP connected");

        timer->start(1000);
        return;
    }

    QMessageBox::warning(this,"Device2 Disconnected","Device2 TCP Disconnected");

}
/**************************************************************************************************************/
void MainWindow::device03_connect_to_dev()
{
    device03_mbTCP.IP = device02_dialog->IPV4_Selected();
    device03_mbTCP.port = device02_dialog->Port_Selected().toInt();
    device03_mbTCP.set_slave(device02_dialog->Slave_Selected().toInt());

    device03_mbTCP.connect();
}

void MainWindow::device03_disconnect_from_dev()
{
    device03_mbTCP.disconnect();
}

void MainWindow::device03_read_regs()
{
    int addr = device03_dialog->Reg_Selected().toInt();
    int count = device03_dialog->Count_Selected().toInt();

    if(count > MODBUS_MAX_READ_REGISTERS)
    {
        QMessageBox::warning(this,"Error Register",QString("Error count reg is: %1 Max count reg is: %2").arg(count).arg(MODBUS_MAX_READ_REGISTERS));
        return;
    }
    if(count <= 0)
    {
        QMessageBox::warning(this,"Error Register",QString("Error count reg is: %1").arg(count));
        return;
    }
    device03_mbTCP.read_regs(addr,count,rd_buf_device03);
}

void MainWindow::device03_response_to_read_regs(int status)
{
    int i;

    if(status<=0)
        return;
    for(i = 0; i < status; i++)
    {
        if(i==0)
        {
            //ui->lcdNumber->display(rd_buf_device03[i]);//แสดงบน ui
        }
        else if(i==1)
        {
            //ui->lcdNumber_2->display(rd_buf_device03[i]);//แสดงบน ui
        }
        else if(i==2)
        {
            //ui->lcdNumber_3->display(rd_buf_device03[i]);//แสดงบน ui
        }
        //ui->log_plain_text_edit->appendPlainText(QString("reg[%1] == %2").arg(i).arg(rd_buf_device02[i]));
    }
}

void MainWindow::device03_process_error(QModBus::ModBusError error)
{
    timer3->stop();//เพื่อไม่ให้ QMessageBox เด้งทุกๆวินาทีตอน error
    switch (error)
    {

        case QModBus::NoConnectionError:
        case QModBus::CreateError:
        case QModBus::ConnectionError:
        {
            QMessageBox::critical(this,"ERROR","Device3 Connection Error or Create Error");
            break;
        }


        case QModBus::ReadRegsError:
        {
            QMessageBox::critical(this,"ERROR","Device3 Read Register Error");
            break;
        }


        case QModBus::WriteRegError:
        {
            QMessageBox::critical(this,"ERROR","Device3 Write Register Error");
            break;
        }


        default:
            break;
    }
}

void MainWindow::device03_change_status()
{
    if(device03_mbTCP.is_connected())
    {
        QMessageBox::information(this,"Device3 Connected","Device3 TCP connected");
        timer3->start(1000);
        return;
    }

    QMessageBox::warning(this,"Device3 Disconnected","Device3 TCP Disconnected");
}
/**************************************************************************************************************/
void MainWindow::device04_connect_to_dev()
{
    device04_mbRTU.device = m_rtu.getComPort();                     //device04_dialog->ComPort_Selected();
    device04_mbRTU.baudrate = m_rtu.getBuadRate().toInt();          //device04_dialog->BuadRate_Selected().toInt();
    device04_mbRTU.parity = m_rtu.getParity().at(0).toLatin1();     //device04_dialog->Parity_Selected().at(0).toLatin1();
    device04_mbRTU.data_bit = m_rtu.getDataBits().toInt();          //device04_dialog->DataBits_Selected().toInt();
    device04_mbRTU.stop_bit = m_rtu.getStopBits().toInt();          //device04_dialog->StopBit_Selected().toInt();
    device04_mbRTU.set_slave(m_rtu.getSlave().toInt());                                     //device04_dialog->Slave_Selected().toInt()

    device04_mbRTU.connect();


}

void MainWindow::device04_disconnect_from_dev()
{
    device04_mbRTU.disconnect();
}

void MainWindow::device04_read_regs()
{
    int addr = m_rtu.getReg().toInt();      //device04_dialog->Reg_Selected().toInt();
    int count = m_rtu.getCount().toInt();   //device04_dialog->Count_Selected().toInt();

    if(count > MODBUS_MAX_READ_REGISTERS)
    {
        QMessageBox::warning(this,"Device04 Error Register",QString("Error count reg is: %1 Max count reg is: %2").arg(count).arg(MODBUS_MAX_READ_REGISTERS));
        return;
    }
    if(count <= 0)
    {
        QMessageBox::warning(this,"Device04 Error Register",QString("Error count reg is: %1").arg(count));
        return;
    }

    device04_mbRTU.read_regs(addr,count,rd_buf_device04);
}

void MainWindow::device04_response_to_read_regs(int status)
{
    int i;

    if(status<=0)
        return;
    for(i = 0; i < status; i++)
    {
        if(i==0)
        {
            //ui->lcdNumber_4->display(rd_buf_device04[i]);//แสดงบน ui
        }
        else if(i==1)
        {
            //ui->lcdNumber_2->display(rd_buf_device03[i]);//แสดงบน ui
        }
        else if(i==2)
        {
            //ui->lcdNumber_3->display(rd_buf_device03[i]);//แสดงบน ui
        }
        //ui->log_plain_text_edit->appendPlainText(QString("reg[%1] == %2").arg(i).arg(rd_buf_device02[i]));
    }
}

void MainWindow::device04_process_error(QModBus::ModBusError error)
{
    timer4->stop();//เพื่อไม่ให้ QMessageBox เด้งทุกๆวินาทีตอน error
    switch (error)
    {

        case QModBus::NoConnectionError:
        case QModBus::CreateError:
        case QModBus::ConnectionError:
        {
            QMessageBox::critical(this,"Device4 ERROR","Connection Error or Create Error");
            device04_mbRTU.disconnect();
            ui->actionMODBUS_RTU->setChecked(false);
            break;
        }


        case QModBus::ReadRegsError:
        {
            QMessageBox::critical(this,"Device4 ERROR","Read Register Error");
            device04_mbRTU.disconnect();
            break;
        }


        case QModBus::WriteRegError:
        {
            QMessageBox::critical(this,"Device4 ERROR","Write Register Error");
            device04_mbRTU.disconnect();
            break;
        }


        default:
            break;
    }
}

void MainWindow::device04_change_status()
{
    if(device04_mbRTU.is_connected())
    {
        QMessageBox::information(this,"Device4 Connected","Device4 RTU connected");
        timer4->start(1000);
        return;
    }

    QMessageBox::warning(this,"Device4 Disconnected","Device4 RTU Disconnected");
}
void MainWindow::newFile()
{
    if(save == true)
    {
        v_x.clear();
        v_y.clear();
        qv_x.clear();
        qv_y.clear();

        v_y1.clear();
        v_y2.clear();
        v_y3.clear();
        v_y4.clear();

        v_y5.clear();
        v_y6.clear();
        v_y7.clear();
        v_y8.clear();

        qv_x1.clear();
        qv_x2.clear();
        qv_x3.clear();
        qv_x4.clear();
        qv_x5.clear();
        qv_x6.clear();
        qv_x7.clear();
        qv_x8.clear();

        qv_y1.clear();
        qv_y2.clear();
        qv_y3.clear();
        qv_y4.clear();

        qv_y5.clear();
        qv_y6.clear();
        qv_y7.clear();
        qv_y8.clear();

        time.clear();

        sec_max = 0;

        range_max = -99999;
        range_min = 99999;

        //ui->plot->addGraph();
        ui->plot->graph(0)->data().data()->clear();
        ui->plot->graph(1)->data().data()->clear();
        ui->plot->graph(2)->data().data()->clear();
        ui->plot->graph(3)->data().data()->clear();
        ui->plot->graph(4)->data().data()->clear();
        ui->plot->graph(5)->data().data()->clear();
        ui->plot->graph(6)->data().data()->clear();
        ui->plot->graph(7)->data().data()->clear();


        ui->plot->replot();
        //ui->GraphName_line->clear();
        //ui->Pressure_line->clear();
        //ui->Temp_line->clear();
        ui->SampleID_LE->clear();
        ui->BasePolymer_LE->clear();
        ui->Customer_LE->clear();
        ui->Date_LE->clear();
        ui->Operator_LE->clear();
        ui->FilterScreenSize_LE->clear();
        ui->PigmentWeight_LE->clear();
        ui->TotalWeight_LE->clear();
        setcurrentFile("untitled.LTN");
    }
    else if(save == false)
    {
        saveFile_MessageBox();
        //normalSave();
        v_x.clear();
        v_y.clear();
        qv_x.clear();
        qv_y.clear();

        v_y1.clear();
        v_y2.clear();
        v_y3.clear();
        v_y4.clear();

        v_y5.clear();
        v_y6.clear();
        v_y7.clear();
        v_y8.clear();

        qv_x1.clear();
        qv_x2.clear();
        qv_x3.clear();
        qv_x4.clear();
        qv_x5.clear();
        qv_x6.clear();
        qv_x7.clear();
        qv_x8.clear();

        qv_y1.clear();
        qv_y2.clear();
        qv_y3.clear();
        qv_y4.clear();

        qv_y5.clear();
        qv_y6.clear();
        qv_y7.clear();
        qv_y8.clear();

        time.clear();

        sec_max = 0;

        range_max = -99999;
        range_min = 99999;

        //ui->plot->addGraph();
        ui->plot->graph(0)->data().data()->clear();
        ui->plot->graph(1)->data().data()->clear();
        ui->plot->graph(2)->data().data()->clear();
        ui->plot->graph(3)->data().data()->clear();
        ui->plot->graph(4)->data().data()->clear();
        ui->plot->graph(5)->data().data()->clear();
        ui->plot->graph(6)->data().data()->clear();
        ui->plot->graph(7)->data().data()->clear();
        ui->plot->replot();
        //ui->GraphName_line->clear();
        //ui->Pressure_line->clear();
        //ui->Temp_line->clear();
        ui->SampleID_LE->clear();
        ui->BasePolymer_LE->clear();
        ui->Customer_LE->clear();
        ui->Date_LE->clear();
        ui->Operator_LE->clear();
        ui->FilterScreenSize_LE->clear();
        ui->PigmentWeight_LE->clear();
        ui->TotalWeight_LE->clear();
        setcurrentFile("untitled.LTN");
    }
    File_is_change_init();
    save = true;
    ui->actionSave->setEnabled(!save);
    ui->SAVE_BTN->setEnabled(!save);
}
void MainWindow::openFile_dialog_exec()
{
    newFile();
    QString filter = "Text Files (*.LTN)";
    QString file_name = QFileDialog::getOpenFileName(this,"Open a file",QDir::homePath(),filter);
    QMessageBox::information(this,"Selected",file_name);


    QFile inputFile(file_name);
    if(inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
         //QString Graph_name;
         //QString P;
         //QString T;

        QString Sample_ID;
        QString Base_polymer;
        QString Customer;
        QString Date;
        QString Operator;
        QString Filter_screen_size;
        QString Pigment_weight;
        QString Total_weight;

        QString Feed_rate;
        QString Pressure_at_gear_pump_inlet;
        QString Filter_test_unit_temp;
        QString Unit_feed_rate;

        QString Unit_Pressure;
        QString Unit_Temperature;

         v_x.clear();
         v_y.clear();
         qv_x.clear();
         qv_y.clear();
         //ui->plot->addGraph();
         ui->plot->graph(0)->data().data()->clear();
         ui->plot->replot();
         int count = 0;
        while(!in.atEnd())
        {
            if(count <1)
            {
                QStringList items = in.readLine().split(',');
                //Graph_name = items.at(0);
                //P = items.at(1);
                //T = items.at(2);
                Sample_ID                   = items.at(0);
                Base_polymer                = items.at(1);
                Customer                    = items.at(2);
                Date                        = items.at(3);
                Operator                    = items.at(4);
                Filter_screen_size          = items.at(5);
                Pigment_weight              = items.at(6);
                Total_weight                = items.at(7);
                Feed_rate                   = items.at(8);
                Pressure_at_gear_pump_inlet = items.at(9);
                Filter_test_unit_temp       = items.at(10);
                Unit_feed_rate              = items.at(11);
                Unit_Pressure               = items.at(12);
                Unit_Temperature            = items.at(13);

            }
            else if(count ==1)
            {
                in.readLine();
            }
            else if(count ==2)
            {
                in.readLine();
            }
            else if(count >2)
            {
                QStringList items = in.readLine().split(',');
                //v_x.push_back(items.at(0).toDouble());
                //v_y.push_back(items.at(1).toDouble());
                time.push_back(items.at(0).toDouble());//t
                v_y4.push_back(items.at(1).toDouble());//P1
                v_y1.push_back(items.at(3).toDouble());//P2
                v_y3.push_back(items.at(5).toDouble());//T1
                v_y2.push_back(items.at(7).toDouble());//T2
            }
            count++;
        }
        inputFile.close();

        setcurrentFile(file_name);

        //ui->GraphName_line->setText(Graph_name);
        //ui->Pressure_line->setText(P);
        //ui->Temp_line->setText(T);

        ui->SampleID_LE->setText(Sample_ID);
        ui->BasePolymer_LE->setText(Base_polymer);
        ui->Customer_LE->setText(Customer);
        ui->Date_LE->setText(Date);
        ui->Operator_LE->setText(Operator);
        ui->FilterScreenSize_LE->setText(Filter_screen_size);
        ui->PigmentWeight_LE->setText(Pigment_weight);
        ui->TotalWeight_LE->setText(Total_weight);
        ui->FeedRate_LE->setText(Feed_rate);
        ui->UnitFeedRate_LB->setText(Unit_feed_rate);
        ui->PressureGearPumpInlet_LE->setText(Pressure_at_gear_pump_inlet);
        ui->FilterTestUnitTemp_LE->setText(Filter_test_unit_temp);

        if(Unit_feed_rate == "cc/min")
        {
            ui->actionCC_Min->setChecked(true);
            ui->actionrpm->setChecked(false);
            ui->UnitFeedRate_LB->setText("cc/min");
        }
        else if(Unit_feed_rate == "rpm")
        {
            UnitChangeFeedRate_RPM();
        }

        if(Unit_Pressure == "psi")
        {
            if(Unit_Temperature == "°C")
            {
                UnitChangePSI_C();
            }
            else if(Unit_Temperature == "°F")
            {
                UnitChangePSI_F();
            }
        }

        if(Unit_Pressure == "bar" && Unit_Temperature == "°C")
        {
            UnitChangeBar_C();
        }


        plotMaxMin.sec_max  = *max_element(time.begin(), time.end());
        double P1_max = *max_element(v_y4.begin(), v_y4.end());
        double P1_min = *min_element(v_y4.begin(), v_y4.end());
        double P2_max = *max_element(v_y1.begin(), v_y1.end());
        double P2_min = *min_element(v_y1.begin(), v_y1.end());
        double T1_max = *max_element(v_y3.begin(), v_y3.end());
        double T1_min = *min_element(v_y3.begin(), v_y3.end());
        double T2_max = *max_element(v_y2.begin(), v_y2.end());
        double T2_min = *min_element(v_y2.begin(), v_y2.end());



        v_maxValue.push_back(P1_max);
        v_minValue.push_back(P1_min);
        v_maxValue.push_back(P2_max);
        v_minValue.push_back(P2_min);
        v_maxValue.push_back(T1_max);
        v_minValue.push_back(T1_min);
        v_maxValue.push_back(T2_max);
        v_minValue.push_back(T2_min);

        range_max = *max_element(v_maxValue.begin(), v_maxValue.end());
        range_min = *min_element(v_minValue.begin(), v_minValue.end());

        //double max_y = *max_element(v_y.begin(), v_y.end());
        //double min_y = *min_element(v_y.begin(), v_y.end());
        //ui->plot->xAxis->setRange(0,max_x); //max_x คือค่ามากสุดที่แกน x จะโชว์ได้
        //ui->plot->yAxis->setRange(min_y,max_y); //max_ัy คือค่ามากสุดที่แกน y จะโชว์ได้
        ui->plot->xAxis->setRange(0,plotMaxMin.sec_max);
        ui->plot->yAxis->setRange(range_min-25,range_max+25);
        ui->plot->yAxis2->setRange(range_min-25,range_max+25);
        for(int i = 0;i<v_y4.size();i++)    //ไม่สนใจบรรทัดแรกคือ count = 0
        {
            //qv_x.append(v_x.at(i));
            //qv_y.append(v_y.at(i));
            //ui->plot->graph(0)->setData(qv_x,qv_y);
            //ui->plot->replot();
            qv_x1.append(time.at(i));
            qv_y1.append(v_y1.at(i));
            ui->plot->graph(1)->setData(qv_x1,qv_y1);

            qv_x2.append(time.at(i));
            qv_y2.append(v_y2.at(i));
            ui->plot->graph(3)->setData(qv_x2,qv_y2);

            qv_x3.append(time.at(i));
            qv_y3.append(v_y3.at(i));
            ui->plot->graph(2)->setData(qv_x3,qv_y3);

            qv_x4.append(time.at(i));
            qv_y4.append(v_y4.at(i));
            ui->plot->graph(0)->setData(qv_x4,qv_y4);

            ui->plot->replot();
        }

        save = true;
        ui->actionSave->setEnabled(!save);
        ui->SAVE_BTN->setEnabled(!save);
        /*connect(ui->GraphName_line,&QLineEdit::textEdited,
                this,&MainWindow::File_is_change);
        connect(ui->Pressure_line,&QLineEdit::textEdited,
                this,&MainWindow::File_is_change);
        connect(ui->Temp_line,&QLineEdit::textEdited,
                this,&MainWindow::File_is_change);*/
    }
}

void MainWindow::Save(const QString &fileName)
{
    QString errorMessage;

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    //QString Graph_Name  = ui->GraphName_line->text();
    //QString Pressure = ui->Pressure_line->text();
    //QString Temp = ui->Temp_line->text();
    QString Sample_ID          = ui->SampleID_LE->text();
    QString Base_polymer       = ui->BasePolymer_LE->text();
    QString Customer           = ui->Customer_LE->text();
    QString Date               = ui->Date_LE->text();
    QString Operator           = ui->Operator_LE->text();
    QString Filter_screen_size = ui->FilterScreenSize_LE->text();
    QString Pigment_weight     = ui->PigmentWeight_LE->text();
    QString Total_weight       = ui->TotalWeight_LE->text();

    QString Feed_rate                   = ui->FeedRate_LE->text();
    QString Pressure_at_gear_pump_inlet = ui->PressureGearPumpInlet_LE->text();
    QString Filter_test_unit_temp       = ui->FilterTestUnitTemp_LE->text();
    QString Unit_feed_rate              = ui->UnitFeedRate_LB->text();

    QString Unit_Pressure               = ui->UnitPStartLB->text();
    QString Unit_Temperature            = ui->UnitTStart_LB->text();


    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        //QTextStream out(&file);
        QTextStream out(&file);
        QString newline = "\n";

        /*Save Data from Line Edit*/
        out <<Sample_ID<<","<<Base_polymer<<","<<Customer<<","<<Date<<","<<Operator<<","
           <<Filter_screen_size<<","<<Pigment_weight<<","<<Total_weight<<","<<Feed_rate<<","
          <<Pressure_at_gear_pump_inlet<<","<<Filter_test_unit_temp<<","<<Unit_feed_rate<<","<<Unit_Pressure<<","<<Unit_Temperature
         <<"\n"<<"\n"<<"t,P1"<<","<<"t,P2"<<","<<"t,T1"<<","<<"t,T2"; //<<"\n"<<"1,2"<<"\n"<<"2,2"<<"\n"<<"3,9"<<"\n"<<"4,50";
        /*End Save Data from Line Edit*/

        /*Plot Graph ถ้าโปรแกรมจริงไม่ต้องใช้*/
        for (int i = 0;i<v_y1.size();i++)
        {
                out << newline;
                out << i <<","<<v_y4[i]<<","<< i <<","<<v_y1[i]<<","<< i <<","<< v_y3[i]<<","<<i<<","<<v_y2[i];
        }
        /*End Plot Graph*/

        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.")
                           .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    } else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                       .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }
    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("Application"), errorMessage);

    }

    save = true;
    ui->actionSave->setEnabled(!save);
    ui->SAVE_BTN->setEnabled(!save);
    setcurrentFile(fileName);
    /*connect(ui->GraphName_line,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change);
    connect(ui->Pressure_line,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change);
    connect(ui->Temp_line,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change);
    statusBar()->showMessage(tr("File saved"), 2000);*/
}

void MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Test"),"",tr("LABTECHTEST (*.LTN);;All Files (*)"));
    //QString Graph_Name  = ui->GraphName_line->text();
    //QString Pressure = ui->Pressure_line->text();
    //QString Temp = ui->Temp_line->text();
    QString Sample_ID          = ui->SampleID_LE->text();
    QString Base_polymer       = ui->BasePolymer_LE->text();
    QString Customer           = ui->Customer_LE->text();
    QString Date               = ui->Date_LE->text();
    QString Operator           = ui->Operator_LE->text();
    QString Filter_screen_size = ui->FilterScreenSize_LE->text();
    QString Pigment_weight     = ui->PigmentWeight_LE->text();
    QString Total_weight       = ui->TotalWeight_LE->text();

    QString Feed_rate          = ui->FeedRate_LE->text();
    QString Pressure_at_gear_pump_inlet = ui->PressureGearPumpInlet_LE->text();
    QString Filter_test_unit_temp  = ui->FilterTestUnitTemp_LE->text();
    QString Unit_feed_rate              = ui->UnitFeedRate_LB->text();

    QString Unit_Pressure               = ui->UnitPStartLB->text();
    QString Unit_Temperature            = ui->UnitTStart_LB->text();

    if(fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::information(this,tr("Unable to open file"),file.errorString());
            return;
        }
        QTextStream out(&file);
        QString newline = "\n";
        out <<Sample_ID<<","<<Base_polymer<<","<<Customer<<","<<Date<<","<<Operator<<","
           <<Filter_screen_size<<","<<Pigment_weight<<","<<Total_weight<<","<<Feed_rate<<","
          <<Pressure_at_gear_pump_inlet<<","<<Filter_test_unit_temp<<","<<Unit_feed_rate<<","<<Unit_Pressure<<","<<Unit_Temperature
         <<"\n"<<"\n"<<"t,P1"<<","<<"t,P2"<<","<<"t,T1"<<","<<"t,T2";
        for (int i = 0;i<v_y1.size();i++)
        {
                out << newline;
                out << i <<","<<v_y4[i]<<","<< i <<","<<v_y1[i]<<","<< i <<","<< v_y3[i]<<","<<i<<","<<v_y2[i];
        }
    }
    save = true;
    ui->actionSave->setEnabled(!save);
    ui->SAVE_BTN->setEnabled(!save);
    statusBar()->showMessage(tr("File saved"), 2000);
    setcurrentFile(fileName);
    /*connect(ui->GraphName_line,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change);
    connect(ui->Pressure_line,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change);
    connect(ui->Temp_line,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change);*/
}

void MainWindow::chooseSave()
{
    if(currFile.isEmpty()||currFile == "*untitled.LTN" || currFile == "untitled.LTN")
    {
        saveAs();
    }
    else{
        Save(currFile);
    }
}

void MainWindow::File_is_change()
{
    save = false;
    //ui->actionSave_2->setEnabled(!save);
    QString showName = currFile;
    QString star = "*";
    QString title = "LTN - "+ star + showName;
    //if(title == "LTN - *untitled.LTN")
    //{
     //   ui->actionSave_2->setEnabled(!save);
   // }
    setWindowTitle(title);
}

void MainWindow::File_is_change_init()
{
    save = false;
    ui->actionSave->setEnabled(!save);
    ui->SAVE_BTN->setEnabled(!save);
    //QString showName = currFile;
    //QString star = "*";
    QString showName = currFile;
    QString star = "*";
    QString title = "LTN - "+ star + showName;
    setWindowTitle(title);
}

void MainWindow::saveFile_MessageBox()
{
    QMessageBox::StandardButton reply =  QMessageBox::warning(this,"LTN","Do you want to changes to " + currFile,
                         QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
    ignore_Close = false;
    if(reply ==QMessageBox::Yes)
    {
        chooseSave();
    }
    else if(reply ==QMessageBox::Cancel)
    {
        ignore_Close = true;
    }
    else
    {
        return;
    }
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(save == false)
    {
        saveFile_MessageBox();
        if(ignore_Close==true)
        {
            event->ignore();
        }
        else
        {
            event->accept();
        }
    }

}

void MainWindow::printPreview()
{
    ui->New_BTN->hide();
    ui->OPEN_BTN->hide();
    setStyleSheet("background-color: white;");
    QPrinter printer;
    QPrintPreviewDialog previewDialog(&printer, this);
    previewDialog.resize(1000,1000);

    connect(&previewDialog, SIGNAL(paintRequested(QPrinter*)), SLOT(renderPlot(QPrinter*))); 
    previewDialog.exec();
    setStyleSheet("background-color: light gray;");
    ui->New_BTN->setVisible(true);
    ui->OPEN_BTN->setVisible(true);
}

void MainWindow::renderPlot(QPrinter *printer)
{
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local(UTC.toLocalTime());
    qDebug()<<local.toString();
      //printer->setPageSize(QPrinter::A4);
    printer->setPaperSize(QSizeF(210, 297), QPrinter::Millimeter); //ใช้แบบนี้ดีกว่า printer->setPageSize(QPrinter::A4);
    printer->setOrientation(QPrinter::Landscape);
      QCPPainter painter(printer);

      painter.begin(printer);
      painter.setMode(QCPPainter::pmVectorized);
      painter.setMode(QCPPainter::pmNoCaching);
      painter.setMode(QCPPainter::pmNonCosmetic);

           //printer->pageRect().width();
      double xscale = printer->pageRect().width() / double(ui->centralWidget->width());
      double yscale = printer->pageRect().height() / double(ui->centralWidget->height());
      double scale = qMin(xscale/1.1, yscale/1.1); //1.1 เพื่อจะได้เว้นจากขอบ
      painter.translate(printer->paperRect().center()); //Adjust ให้อยู่จรงกลาง

      painter.scale(scale, scale);
      painter.translate(-width()/2, -height()/2);
           //ui->centralwidget->render(&painter);
           //ui->centralwidget->grab();
      m_image = ui->centralWidget->grab();
           //painter.drawImage(QRect(0, 100, 500, 500), QImage("C:/Users/KOM/Desktop/kkk.png"));
      m_image.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);

      painter.drawPixmap(0,0,m_image);
      painter.drawText(0, 0, 500, 500, Qt::AlignLeft, local.toString());
           //ui->plot->toPainter(&painter, xscale, yscale);
      painter.end();
}

void MainWindow::setcurrentFile(const QString &fileName)
{
    currFile = fileName;
     //textEdit->document()->setModified(false);
     setWindowModified(false);
     QString showName;
     //QString star = "*";
     if (currFile.isEmpty())
        showName = "untitled.LTN";
     else
        showName = currFile;
     QString title = "LTN - "+ showName;
     setWindowTitle(title);
     ui->FileName_LE->setText(QFileInfo(fileName).fileName());
}

QString MainWindow::SplitCode(QStringList text, int *before, int *after)
{
    QString num;
    for(int i =*before +1;i<=*after-1;i++)
    {
        num += text.at(i);
    }
    return num;
}
/*************************************************************************************************************/
void MainWindow::serialport_Constructor()
{
    TestSerial = new QTimer(this);
    QObject::connect(TestSerial, &QTimer::timeout,
                     this, &MainWindow::device01_write);
    serial.close();
}

void MainWindow::modbus_tcp_dv02_Constructor()
{
    QObject::connect(&device02_mbTCP,  SIGNAL(error(QModBus::ModBusError)),
                     this, SLOT(device02_process_error(QModBus::ModBusError)));  //dv2


    QObject::connect(&device02_mbTCP,  SIGNAL(connected()),
                     this, SLOT(device02_change_status()));                     //dv2

    QObject::connect(&device02_mbTCP,  SIGNAL(disconnected()),
                     this, SLOT(device02_change_status()));                     //dv2

    QObject::connect(&device02_mbTCP,&QModBus::response_to_read_regs,
                     this,&MainWindow::device02_response_to_read_regs);         //dv2

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()),
                     this, SLOT(device02_read_regs()));                         //dv2

    device02_mbTCP.disconnect();
}

void MainWindow::modbus_tcp_dv03_Constructor()
{
    QObject::connect(&device03_mbTCP,  SIGNAL(error(QModBus::ModBusError)),
                     this, SLOT(device03_process_error(QModBus::ModBusError)));     //dv3


    QObject::connect(&device03_mbTCP,  SIGNAL(connected()),
                     this, SLOT(device03_change_status()));                         //dv3

    QObject::connect(&device03_mbTCP,  SIGNAL(disconnected()),
                     this, SLOT(device03_change_status()));                         //dv3

    QObject::connect(&device03_mbTCP,&QModBus::response_to_read_regs,
                     this,&MainWindow::device03_response_to_read_regs);             //dv3

    timer3 = new QTimer(this);
    QObject::connect(timer3, SIGNAL(timeout()),
                     this, SLOT(device03_read_regs()));                             //dv3
}

void MainWindow::modbus_rtu_dv04_Constructor()
{
    QObject::connect(&device04_mbRTU,  SIGNAL(error(QModBus::ModBusError)),
                     this, SLOT(device04_process_error(QModBus::ModBusError)));     //dv4

    QObject::connect(&device04_mbRTU,  SIGNAL(connected()),
                     this, SLOT(device04_change_status()));                         //dv4

    QObject::connect(&device04_mbRTU,  SIGNAL(disconnected()),
                     this, SLOT(device04_change_status()));                         //dv4

    QObject::connect(&device04_mbRTU,&QModBus::response_to_read_regs,
                     this,&MainWindow::device04_response_to_read_regs);             //dv4

    timer4 = new QTimer(this);
    QObject::connect(timer4, SIGNAL(timeout()),
                     this, SLOT(device04_read_regs()));                             //dv4

    device04_mbRTU.disconnect();
}

void MainWindow::device_action_Constructor()
{
    connect(ui->actionDevice1,&QAction::triggered,
            this,&MainWindow::device01_dialog_exec);    /*Device01 Normal Serialport*/

    connect(ui->actionMODBUS_TCP,&QAction::triggered,
            this,&MainWindow::device02_dialog_exec);    /*Device02 TCP*/

    connect(ui->actionMODBUS_TCP_3,&QAction::triggered, /*Device03 TCP UNUSE*/
            this,&MainWindow::device03_dialog_exec);

    connect(ui->actionMODBUS_RTU,&QAction::triggered,
            this,&MainWindow::device04_dialog_exec);    /*Device04 RTU*/

    connect(ui->actionCC_Min,&QAction::triggered,
            this,&MainWindow::feedrate_dialog_exec);
    scale.setCc_min_scale("1.5");  //ของ feedrate factor
    ui->actionCC_Min->setChecked(true);

    value.setTime("1000");          //ของปุ่ม start
}

void MainWindow::file_action_Constructor()
{
    connect(ui->actionNew,&QAction::triggered,
            this,&MainWindow::newFile);

    connect(ui->actionOpen_File,&QAction::triggered,
            this,&MainWindow::openFile_dialog_exec);

    connect(ui->actionSave,&QAction::triggered,
            this,&MainWindow::chooseSave);

    connect(ui->actionSave_As,&QAction::triggered,
            this,&MainWindow::saveAs);

    connect(ui->actionPrint,&QAction::triggered,
            this,&MainWindow::printPreview);

    setcurrentFile("untitled.LTN");

    save = true;
    ui->actionSave->setEnabled(!save);
    ui->SAVE_BTN->setEnabled(!save);
}

void MainWindow::change_unit_action_Constructor()
{
    ui->actionpsi_C->setChecked(true);

    connect(ui->actionbar_C,&QAction::triggered,
            this,&MainWindow::UnitChangeBar_C);
    connect(ui->actionpsi_C,&QAction::triggered,
            this,&MainWindow::UnitChangePSI_C);
    connect(ui->actionpsi_F,&QAction::triggered,
            this,&MainWindow::UnitChangePSI_F);
    connect(ui->actionrpm,&QAction::triggered,
            this,&MainWindow::UnitChangeFeedRate_RPM);
}

void MainWindow::graph_Constructor()
{
    QPen pen0;
    pen0.setColor(QColor(0,0,255)); //blue
    pen0.setWidth(1);
    ui->plot->addGraph();
    ui->plot->graph(0);
    ui->plot->graph(0)->setPen(QPen(pen0));
    ui->plot->graph(0)->setName("P1");


    ui->plot->xAxis->setLabel("Time (sec)");

    ui->plot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->plot->xAxis->grid()->setSubGridVisible(true);
    ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->plot->yAxis->grid()->setSubGridVisible(true);
    ui->plot->yAxis2->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->plot->yAxis2->grid()->setSubGridVisible(true);
    ui->plot->yAxis2->grid()->setVisible(true);

    ui->plot->yAxis->setLabel("Pressure[psi] , Ampere(%)");
    ui->plot->yAxis2->setRange(0,10);
    ui->plot->yAxis2->setLabel("Melt temperature[°C] , Speed(RPM)");
    ui->plot->yAxis2->setVisible(true);

    ui->plot->addGraph();
    ui->plot->graph(1);
    ui->plot->graph(1)->setPen(QPen(QColor(255,0,0)));  //red
    ui->plot->graph(1)->setName("P2");

    ui->plot->addGraph(ui->plot->xAxis,ui->plot->yAxis2);
    ui->plot->graph(2);
    ui->plot->graph(2)->setPen(QPen(QColor(0,0,0)));  //black
    ui->plot->graph(2)->setName("T1");//Melt temperature1

    ui->plot->addGraph(ui->plot->xAxis,ui->plot->yAxis2);
    ui->plot->graph(3);
    ui->plot->graph(3)->setPen(QPen(QColor(0,204,0)));//green
    ui->plot->graph(3)->setName("T2");//Melt temperature2

    ui->plot->addGraph();
    ui->plot->graph(4);
    ui->plot->graph(4)->setPen(QPen(QColor(102,102,0)));  //black green
    ui->plot->graph(4)->setName("A1");

    ui->plot->addGraph();
    ui->plot->graph(5);
    ui->plot->graph(5)->setPen(QPen(QColor(0,0,102)));  //black blue
    ui->plot->graph(5)->setName("A2");

    ui->plot->addGraph(ui->plot->xAxis,ui->plot->yAxis2);
    ui->plot->graph(6);
    ui->plot->graph(6)->setPen(QPen(QColor(255,128,0)));  //black
    ui->plot->graph(6)->setName("Ext");//Extruder

    ui->plot->addGraph(ui->plot->xAxis,ui->plot->yAxis2);
    ui->plot->graph(7);
    ui->plot->graph(7)->setPen(QPen(QColor(0,255,255)));  //black
    ui->plot->graph(7)->setName("Gp");//Gearpump

    ui->plot->legend->setFont(QFont(font().family(), 7));
    ui->plot->legend->setIconSize(50, 20);
    ui->plot->legend->setVisible(true);

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->plot->plotLayout()->addElement(1, 0, subLayout);
    subLayout->setMargins(QMargins(5, 0, 5, 5));
    subLayout->addElement(0, 0, ui->plot->legend);
    // change the fill order of the legend, so it's filled left to right in columns:
    ui->plot->legend->setFillOrder(QCPLegend::foColumnsFirst);
    // set legend's row stretch factor very small so it ends up with minimum height:
    ui->plot->plotLayout()->setRowStretchFactor(1, 0.001);


    //ui->plot->graph(2)->setVisible(false);//ซ่อนกราฟ
    //ui->plot->legend->removeItem(2);//ซ่อน legend
    icount = 0;
}

void MainWindow::file_is_change_Constructor()
{
    connect(ui->SampleID_LE,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change_init);
    connect(ui->BasePolymer_LE,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change_init);
    connect(ui->Customer_LE,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change_init);
    connect(ui->Date_LE,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change_init);
    connect(ui->Operator_LE,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change_init);

    connect(ui->FilterScreenSize_LE,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change_init);
    connect(ui->PigmentWeight_LE,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change_init);
    connect(ui->TotalWeight_LE,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change_init);
}

void MainWindow::disconnect_button_Constructor()
{
    ui->SerialPort_BTN->setEnabled(false);
    ui->SerialPort_BTN->setChecked(false);
}

void MainWindow::Hide_And_Show_All_Graph()
{
   if(ui->actionAll->isChecked())
   {
       ui->actionP1->setChecked(true);
       ui->actionP2->setChecked(true);
       ui->actionT1->setChecked(true);
       ui->actionT2->setChecked(true);
       ui->actionP1O->setChecked(true);
       ui->actionP2O->setChecked(true);
       ui->actionT1O->setChecked(true);
       ui->actionT2O->setChecked(true);
       ui->actionExt->setChecked(true);
       ui->actionA1->setChecked(true);
       ui->actionGp->setChecked(true);
       ui->actionA2->setChecked(true);
       ui->actionExtO->setChecked(true);
       ui->actionA1O->setChecked(true);
       ui->actionGpO->setChecked(true);
       ui->actionA2O->setChecked(true);
   }
   else if(!ui->actionAll->isChecked())
   {
       ui->actionP1->setChecked(true);
       ui->actionP2->setChecked(true);
       ui->actionT1->setChecked(true);
       ui->actionT2->setChecked(true);
       ui->actionP1O->setChecked(false);
       ui->actionP2O->setChecked(false);
       ui->actionT1O->setChecked(false);
       ui->actionT2O->setChecked(false);
       ui->actionExt->setChecked(true);
       ui->actionA1->setChecked(true);
       ui->actionGp->setChecked(true);
       ui->actionA2->setChecked(true);
       ui->actionExtO->setChecked(false);
       ui->actionA1O->setChecked(false);
       ui->actionGpO->setChecked(false);
       ui->actionA2O->setChecked(false);
   }
}

void MainWindow::Hide_And_Show_P1_Graph()
{
    if(!ui->actionP1->isChecked())
    {
        ui->plot->graph(0);
        ui->plot->graph(0)->setVisible(false);//ซ่อนกราฟ
        ui->plot->graph(0)->removeFromLegend();//ซ่อน legend
        ui->plot->replot();
    }
    else if(ui->actionP1->isChecked())
    {
        ui->plot->graph(0);
        ui->plot->graph(0)->setVisible(true);//ซ่อนกราฟ
        ui->plot->graph(0)->addToLegend();//ซ่อน legend
        ui->plot->replot();
    }
}

void MainWindow::Hide_And_Show_P2_Graph()
{
    if(!ui->actionP2->isChecked())
    {
        ui->plot->graph(1);
        ui->plot->graph(1)->setVisible(false);//ซ่อนกราฟ
        ui->plot->graph(1)->removeFromLegend();//ซ่อน legend
        ui->plot->replot();
    }
    else if(ui->actionP2->isChecked())
    {
        ui->plot->graph(1);
        ui->plot->graph(1)->setVisible(true);//ซ่อนกราฟ
        ui->plot->graph(1)->addToLegend();//ซ่อน legend
        ui->plot->replot();
    }

}

void MainWindow::Hide_And_Show_T1_Graph()
{
    if(!ui->actionT1->isChecked())
    {
        ui->plot->graph(2);
        ui->plot->graph(2)->setVisible(false);//ซ่อนกราฟ
        ui->plot->graph(2)->removeFromLegend();
        ui->plot->replot();
    }
    else if(ui->actionT1->isChecked())
    {
        ui->plot->graph(2);
        ui->plot->graph(2)->setVisible(true);//ซ่อนกราฟ
        ui->plot->graph(2)->addToLegend();//ซ่อน legend
        ui->plot->replot();
    }
}

void MainWindow::Hide_And_Show_T2_Graph()
{
    if(!ui->actionT2->isChecked())
    {
        ui->plot->graph(3);
        ui->plot->graph(3)->setVisible(false);//ซ่อนกราฟ
        ui->plot->graph(3)->removeFromLegend();
        ui->plot->replot();
    }
    else if(ui->actionT2->isChecked())
    {
        ui->plot->graph(3);
        ui->plot->graph(3)->setVisible(true);//ซ่อนกราฟ
        ui->plot->graph(3)->addToLegend();//ซ่อน legend
        ui->plot->replot();
    }
}

void MainWindow::Hide_And_Show_P1O_Graph()
{

}

void MainWindow::Hide_And_Show_P2O_Graph()
{

}

void MainWindow::Hide_And_Show_T1O_Graph()
{

}

void MainWindow::Hide_And_Show_T2O_Graph()
{

}

void MainWindow::Hide_And_Show_Ext_Graph()
{
    if(!ui->actionExt->isChecked())
    {
        ui->plot->graph(6);
        ui->plot->graph(6)->setVisible(false);//ซ่อนกราฟ
        ui->plot->graph(6)->removeFromLegend();
        ui->plot->replot();
    }
    else if(ui->actionExt->isChecked())
    {
        ui->plot->graph(6);
        ui->plot->graph(6)->setVisible(true);//ซ่อนกราฟ
        ui->plot->graph(6)->addToLegend();//ซ่อน legend
        ui->plot->replot();
    }
}

void MainWindow::Hide_And_Show_A1_Graph()
{
    if(!ui->actionA1->isChecked())
    {
        ui->plot->graph(4);
        ui->plot->graph(4)->setVisible(false);//ซ่อนกราฟ
        ui->plot->graph(4)->removeFromLegend();
        ui->plot->replot();
    }
    else if(ui->actionA1->isChecked())
    {
        ui->plot->graph(4);
        ui->plot->graph(4)->setVisible(true);//ซ่อนกราฟ
        ui->plot->graph(4)->addToLegend();//ซ่อน legend
        ui->plot->replot();
    }
}

void MainWindow::Hide_And_Show_Gp_Graph()
{
    if(!ui->actionGp->isChecked())
    {
        ui->plot->graph(7);
        ui->plot->graph(7)->setVisible(false);//ซ่อนกราฟ
        ui->plot->graph(7)->removeFromLegend();
        ui->plot->replot();
    }
    else if(ui->actionGp->isChecked())
    {
        ui->plot->graph(7);
        ui->plot->graph(7)->setVisible(true);//ซ่อนกราฟ
        ui->plot->graph(7)->addToLegend();//ซ่อน legend
        ui->plot->replot();
    }
}

void MainWindow::Hide_And_Show_A2_Graph()
{
    if(!ui->actionA2->isChecked())
    {
        ui->plot->graph(5);
        ui->plot->graph(5)->setVisible(false);//ซ่อนกราฟ
        ui->plot->graph(5)->removeFromLegend();
        ui->plot->replot();
    }
    else if(ui->actionA2->isChecked())
    {
        ui->plot->graph(5);
        ui->plot->graph(5)->setVisible(true);//ซ่อนกราฟ
        ui->plot->graph(5)->addToLegend();//ซ่อน legend
        ui->plot->replot();
    }
}

void MainWindow::Hide_And_Show_ExtO_Graph()
{

}

void MainWindow::Hide_And_Show_A1O_Graph()
{

}

void MainWindow::Hide_And_Show_GpO_Graph()
{

}

void MainWindow::Hide_And_Show_A2O_Graph()
{

}


/**************************************************************************************************************/
void MainWindow::device01_dialog_exec()
{
    device01_dialog = new Device01_Dialog(this);
    device01_dialog->setSerialport(m_serialport);
    device01_dialog->exec();


    m_serialport = device01_dialog->serialport();
    if(device01_dialog->OkBTN()=="OK") //check ว่า device02_dialog กด OK หรือ CANCEL ต้องลองรับค่ามาจาก Qmessagebox connected
    {
        device01_connect_to_dev();
    }
    else if(device01_dialog->OkBTN()=="CANCEL")
    {

    }
    delete device01_dialog;
}

void MainWindow::device02_dialog_exec()
{
    device02_dialog = new Device02_dialog(this);
    device02_dialog->setTcp(m_tcp);
    device02_dialog->exec();

    m_tcp = device02_dialog->tcp();
    if(device02_dialog->OkBTN()=="OK") //check ว่า device02_dialog กด OK หรือ CANCEL ต้องลองรับค่ามาจาก Qmessagebox connected
    {
        device02_connect_to_dev();
        if(device02_mbTCP.is_connected()==true)
        {
            ui->actionMODBUS_TCP->setChecked(true);
            qDebug()<<"connected";
        }

    }
    else if(device02_dialog->OkBTN()=="CANCEL")
    {
        if(device02_mbTCP.is_connected()==true)
            ui->actionMODBUS_TCP->setChecked(true);
        else
            ui->actionMODBUS_TCP->setChecked(false);

    }
    qDebug()<<device02_dialog->OkBTN();
    qDebug()<<device02_mbTCP.is_connected()<<"\n***********";

    delete device02_dialog;
}

void MainWindow::device03_dialog_exec()
{
    device03_dialog = new Device03_Dialog(this);
    device03_dialog->exec();
}

void MainWindow::device04_dialog_exec()
{
    device04_dialog = new Device04_dialog(this);
    device04_dialog->setRtu(m_rtu);
    device04_dialog->exec();

    m_rtu = device04_dialog->rtu();
    if(device04_dialog->OkBTN()=="OK") //check ว่า device02_dialog กด OK หรือ CANCEL
    {
        device04_connect_to_dev();
    }
    else if(device04_dialog->OkBTN()=="CANCEL")
    {
        if(device04_mbRTU.is_connected()==true)
            ui->actionMODBUS_RTU->setChecked(true);
        else
            ui->actionMODBUS_RTU->setChecked(false);
    }
    qDebug()<<device04_dialog->OkBTN();

    delete device04_dialog;
}

void MainWindow::feedrate_dialog_exec()
{
    qDebug()<<scale.getCc_min_scale().toDouble();
    feedrate_dialog = new FeedRate_Dialog(this);
    feedrate_dialog->setScale(scale);
    feedrate_dialog->exec();
    qDebug()<<feedrate_dialog->OkBTN();
    scale = feedrate_dialog->getScale();
    if(feedrate_dialog->OkBTN()=="OK")
    {
        double num = feedrate_dialog->getScale().getCc_min_scale().toDouble();
        qDebug()<<feedrate_dialog->getScale().getCc_min_scale().toDouble();
        qDebug()<<9.5*scale.getCc_min_scale().toDouble();

        ui->actionCC_Min->setText(QString("cc/min (%1)").arg(num));
        ui->actionCC_Min->setChecked(true);
        ui->actionrpm->setChecked(false);
        ui->UnitFeedRate_LB->setText("cc/min");
    }
    else if(feedrate_dialog->OkBTN()=="CANCEL")
    {
        ui->actionCC_Min->setChecked(true);
        ui->actionrpm->setChecked(false);
        ui->UnitFeedRate_LB->setText("cc/min");
    }

    delete feedrate_dialog;
}

void MainWindow::start_dialog_exec()
{
    sec=0;
    start_dialog = new Start_Dialog(this);
    start_dialog->setValue(value);
    start_dialog->exec();
    value = start_dialog->getValue();
    RunTime->stop();
    if(start_dialog->okBTN()=="OK")
    {
        if(start_dialog->getValue().getChoose()==false)
        {
            //qDebug()<<"Time = "<<value.getTime().toInt();
            qDebug()<<"Choose "<<value.getChoose();
            ui->START_BTN->setEnabled(false);
            ui->END_BTN->setEnabled(true);
            RunTime->start(1000);
            //connect(RunTime, &QTimer::timeout,
                    //this, &MainWindow::device01_read);ไปพล็อตกราฟ
        }
        else if(start_dialog->getValue().getChoose()==true)
        {
            //qDebug()<<"Time = "<<value.getTime().toInt();
            qDebug()<<"Choose "<<value.getChoose();
            //StartTime->start(value.getTime().toInt());
            ui->START_BTN->setEnabled(false);
            ui->END_BTN->setEnabled(true);
            RunTime->start(1000);
            //connect(StartTime, &QTimer::timeout,
                    //this, &MainWindow::stop_time);
        }
        delete start_dialog;
    }
    else if(start_dialog->okBTN()=="CANCEL")
    {
        delete start_dialog;
    }

}


/*****************************************************************/







/*****************************************************************/

void MainWindow::on_pushButton_clicked()//ต่อด้วยปุ่มรีเซทใน startbutton
{
    device01_write();
    //ui->FeedRate_LE->setText(scale.getCc_min_scale());
}

void MainWindow::UnitChangeBar_C()
{
    ui->actionbar_C->setChecked(true);
    ui->actionpsi_C->setChecked(false);
    ui->actionpsi_F->setChecked(false);

    ui->UnitPStartLB->setText("bar");
    ui->UnitPMaxLB->setText("bar");
    ui->UnitDelPLB->setText("bar");
    ui->UnitFPVLB->setText("bar/g");

    ui->UnitPInletStart_LB->setText("bar");
    ui->UnitPEndInlet_LB->setText("bar");

    ui->UnitPressureGearPumpInlet_LB->setText("bar");
    ui->UnitFilterTestUnitTemp_LB->setText("°C");

    ui->UnitMeltPressure_LCD->setText("bar");
    ui->UnitMeltTemp_LCD->setText("°C");

    ui->UnitTStart_LB->setText("°C");
    ui->UnitTEnd_LB->setText("°C");
    ui->UnitTMax_LB->setText("°C");
    ui->UnitTMin_LB->setText("°C");

    ui->UnitTStartPumpInlet_LB->setText("°C");
    ui->UnitTEndPumpInlet_LB->setText("°C");

    ui->plot->yAxis->setLabel("Pressure[bar] , Ampere(%)");
    ui->plot->yAxis2->setLabel("Melt temperature[°C] , Speed(RPM)");
    ui->plot->replot();
}

void MainWindow::UnitChangePSI_F()
{
    ui->actionpsi_F->setChecked(true);
    ui->actionbar_C->setChecked(false);
    ui->actionpsi_C->setChecked(false);

    ui->UnitPStartLB->setText("psi");
    ui->UnitPMaxLB->setText("psi");
    ui->UnitDelPLB->setText("psi");
    ui->UnitFPVLB->setText("psi/g");

    ui->UnitPInletStart_LB->setText("psi");
    ui->UnitPEndInlet_LB->setText("psi");

    ui->UnitPressureGearPumpInlet_LB->setText("psi");
    ui->UnitFilterTestUnitTemp_LB->setText("°F");

    ui->UnitMeltPressure_LCD->setText("psi");
    ui->UnitMeltTemp_LCD->setText("°F");

    ui->UnitTStart_LB->setText("°F");
    ui->UnitTEnd_LB->setText("°F");
    ui->UnitTMax_LB->setText("°F");
    ui->UnitTMin_LB->setText("°F");

    ui->UnitTStartPumpInlet_LB->setText("°F");
    ui->UnitTEndPumpInlet_LB->setText("°F");

    ui->plot->yAxis->setLabel("Pressure[psi] , Ampere(%)");
    ui->plot->yAxis2->setLabel("Melt temperature[°F] , Speed(RPM)");
    ui->plot->replot();

}

void MainWindow::UnitChangePSI_C()
{
    ui->actionpsi_C->setChecked(true);
    ui->actionbar_C->setChecked(false);
    ui->actionpsi_F->setChecked(false);

    ui->UnitPStartLB->setText("psi");
    ui->UnitPMaxLB->setText("psi");
    ui->UnitDelPLB->setText("psi");
    ui->UnitFPVLB->setText("psi/g");

    ui->UnitPInletStart_LB->setText("psi");
    ui->UnitPEndInlet_LB->setText("psi");

    ui->UnitPressureGearPumpInlet_LB->setText("psi");
    ui->UnitFilterTestUnitTemp_LB->setText("°C");

    ui->UnitMeltPressure_LCD->setText("psi");
    ui->UnitMeltTemp_LCD->setText("°C");

    ui->UnitTStart_LB->setText("°C");
    ui->UnitTEnd_LB->setText("°C");
    ui->UnitTMax_LB->setText("°C");
    ui->UnitTMin_LB->setText("°C");

    ui->UnitTStartPumpInlet_LB->setText("°C");
    ui->UnitTEndPumpInlet_LB->setText("°C");

    ui->plot->yAxis->setLabel("Pressure[psi] , Ampere(%)");
    ui->plot->yAxis2->setLabel("Melt temperature[°C] , Speed(RPM)");
    ui->plot->replot();
}

void MainWindow::UnitChangeFeedRate_RPM()
{
    ui->actionrpm->setChecked(true);
    ui->actionCC_Min->setChecked(false);
    ui->UnitFeedRate_LB->setText("rpm");
}

void MainWindow::on_New_BTN_clicked()
{
    newFile();
}

void MainWindow::on_OPEN_BTN_clicked()
{
    openFile_dialog_exec();
}

void MainWindow::on_SAVE_BTN_clicked()
{
    /*if(ui->actionSave->isEnabled())
    {
        ui->SAVE_BTN->isEnabled();
        chooseSave();
    }
    else
    {
        ui->SAVE_BTN->setEnabled(false);
    }*/
    chooseSave();
}

void MainWindow::on_PRINT_BTN_clicked()
{
    printPreview();
}

void MainWindow::on_SerialPort_BTN_clicked()
{
    device01_disconnect_from_dev();
}

void MainWindow::on_Reset_Data_BTN_clicked()
{
    //v_y1.erase(v_y1.begin());
    //v_y2.erase(v_y2.begin());
    //v_y3.erase(v_y3.begin());

    v_y1.clear();
    v_y2.clear();
    v_y3.clear();
    v_y4.clear();

    qv_y1.clear();
    qv_y2.clear();
    qv_y3.clear();
    qv_y4.clear();

    ui->PStart_LE->clear();
    ui->PMax_LE->clear();
    ui->DelP_LE->clear();
    ui->FPV_LE->clear();

    ui->PressStartPumpInlet_LE->clear();
    ui->PressEndPumpInlet_LE->clear();

    ui->ScrewSpeed_LE->clear();
    ui->ExtruderAmp_LE->clear();

    ui->TStart_LE->clear();
    ui->TEnd_LE->clear();
    ui->TMax_LE->clear();
    ui->TMin_LE->clear();

    ui->TempStartPumpInlet_LE->clear();
    ui->TempEndPumpInlet_LE->clear();

    ui->GearPumpFeedRate_LE->clear();
    ui->GearPumpAmp_LE->clear();

    sec = 0;
}

void MainWindow::on_START_BTN_clicked()
{
    start_dialog_exec();
    on_pushButton_clicked();//
    on_Reset_Data_BTN_clicked();//
    File_is_change_init();
}

void MainWindow::tiktok()
{
    sec = sec + 1;
    qDebug() <<"Time = "<< sec;
     device01_write();
     /*
     *
     *
     *
     */
    if(sec == value.getTime().toInt())
    {
        RunTime->stop();
        ui->START_BTN->setEnabled(true);
        ui->END_BTN->setEnabled(false);
        sec=0;
    }
}

void MainWindow::on_END_BTN_clicked()
{
    RunTime->stop();
    ui->START_BTN->setEnabled(true);
    ui->END_BTN->setEnabled(false);
}

void MainWindow::mouseWheel()//03042022
{
    if(ui->plot->graph(0)->selected())
    {
        checker.isFit_click = false;
        QPen pen;
        pen.setWidth(5);
        pen.setColor(QColor(0,0,255));
        ui->plot->graph(0)->selectionDecorator()->setPen(pen);
        ui->plot->axisRect()->setRangeZoomAxes(ui->plot->xAxis,ui->plot->yAxis);
        ui->plot->axisRect()->setRangeZoom(ui->plot->xAxis->orientation()|ui->plot->yAxis->orientation());
        ui->plot->axisRect()->setRangeDrag(ui->plot->xAxis->orientation()|ui->plot->yAxis->orientation());
    }
    else if(ui->plot->graph(1)->selected())
    {
        checker.isFit_click = false;
        QPen pen;
        pen.setWidth(5);
        pen.setColor(QColor(255,0,0));
        ui->plot->graph(1)->selectionDecorator()->setPen(pen);
        ui->plot->axisRect()->setRangeZoomAxes(ui->plot->xAxis,ui->plot->yAxis);
        ui->plot->axisRect()->setRangeZoom(ui->plot->xAxis->orientation()|ui->plot->yAxis->orientation());
        ui->plot->axisRect()->setRangeDrag(ui->plot->xAxis->orientation()|ui->plot->yAxis->orientation());
    }
    else if(ui->plot->graph(2)->selected())
    {
        checker.isFit_click = false;
        QPen pen;
        pen.setWidth(5);
        pen.setColor(QColor(0,0,0));
        ui->plot->graph(2)->selectionDecorator()->setPen(pen);
        ui->plot->axisRect()->setRangeZoomAxes(ui->plot->xAxis,ui->plot->yAxis2);
        ui->plot->axisRect()->setRangeZoom(ui->plot->xAxis->orientation()|ui->plot->yAxis2->orientation());
        ui->plot->axisRect()->setRangeDrag(ui->plot->xAxis->orientation()|ui->plot->yAxis2->orientation());
    }
    else if(ui->plot->graph(3)->selected())
    {
        checker.isFit_click = false;
        QPen pen;
        pen.setWidth(5);
        pen.setColor(QColor(0,204,0));
        ui->plot->graph(3)->selectionDecorator()->setPen(pen);
        ui->plot->axisRect()->setRangeZoomAxes(ui->plot->xAxis,ui->plot->yAxis2);
        ui->plot->axisRect()->setRangeZoom(ui->plot->xAxis->orientation()|ui->plot->yAxis2->orientation());
        ui->plot->axisRect()->setRangeDrag(ui->plot->xAxis->orientation()|ui->plot->yAxis2->orientation());
    }
    else if(ui->plot->graph(4)->selected())
    {
        checker.isFit_click = false;
        QPen pen;
        pen.setWidth(5);
        pen.setColor(QColor(102,102,0));
        ui->plot->graph(4)->selectionDecorator()->setPen(pen);
        ui->plot->axisRect()->setRangeZoomAxes(ui->plot->xAxis,ui->plot->yAxis);
        ui->plot->axisRect()->setRangeZoom(ui->plot->xAxis->orientation()|ui->plot->yAxis->orientation());
        ui->plot->axisRect()->setRangeDrag(ui->plot->xAxis->orientation()|ui->plot->yAxis->orientation());
    }
    else if(ui->plot->graph(5)->selected())
    {
        checker.isFit_click = false;
        QPen pen;
        pen.setWidth(5);
        pen.setColor(QColor(0,0,102));
        ui->plot->graph(5)->selectionDecorator()->setPen(pen);
        ui->plot->axisRect()->setRangeZoomAxes(ui->plot->xAxis,ui->plot->yAxis);
        ui->plot->axisRect()->setRangeZoom(ui->plot->xAxis->orientation()|ui->plot->yAxis->orientation());
        ui->plot->axisRect()->setRangeDrag(ui->plot->xAxis->orientation()|ui->plot->yAxis->orientation());
    }
    else if(ui->plot->graph(6)->selected())
    {
        checker.isFit_click = false;
        QPen pen;
        pen.setWidth(5);
        pen.setColor(QColor(255,128,0));
        ui->plot->graph(6)->selectionDecorator()->setPen(pen);
        ui->plot->axisRect()->setRangeZoomAxes(ui->plot->xAxis,ui->plot->yAxis2);
        ui->plot->axisRect()->setRangeZoom(ui->plot->xAxis->orientation()|ui->plot->yAxis2->orientation());
        ui->plot->axisRect()->setRangeDrag(ui->plot->xAxis->orientation()|ui->plot->yAxis2->orientation());
    }
    else if(ui->plot->graph(7)->selected())
    {
        checker.isFit_click = false;
        QPen pen;
        pen.setWidth(5);
        pen.setColor(QColor(0,255,255));
        ui->plot->graph(7)->selectionDecorator()->setPen(pen);
        ui->plot->axisRect()->setRangeZoomAxes(ui->plot->xAxis,ui->plot->yAxis2);
        ui->plot->axisRect()->setRangeZoom(ui->plot->xAxis->orientation()|ui->plot->yAxis2->orientation());
        ui->plot->axisRect()->setRangeDrag(ui->plot->xAxis->orientation()|ui->plot->yAxis2->orientation());
    }
    else
    {
        ui->plot->axisRect()->setRangeZoom(0);
    }
}

void MainWindow::mousePress()//03042022
{
    if(ui->plot->graph(0)->selected())
    {
        checker.isFit_click = false;
        ui->plot->axisRect()->setRangeDragAxes(ui->plot->xAxis,ui->plot->yAxis);
        ui->plot->yAxis2->setRange(ui->plot->yAxis->range());
    }
    else if(ui->plot->graph(1)->selected())
    {
        checker.isFit_click = false;
        ui->plot->axisRect()->setRangeDragAxes(ui->plot->xAxis,ui->plot->yAxis);
        ui->plot->yAxis2->setRange(ui->plot->yAxis->range());
    }
    else if(ui->plot->graph(2)->selected())
    {
        checker.isFit_click = false;
        ui->plot->axisRect()->setRangeDragAxes(ui->plot->xAxis,ui->plot->yAxis2);
        ui->plot->yAxis->setRange(ui->plot->yAxis2->range());
    }
    else if(ui->plot->graph(3)->selected())
    {
        checker.isFit_click = false;
        ui->plot->axisRect()->setRangeDragAxes(ui->plot->xAxis,ui->plot->yAxis2);
        ui->plot->yAxis->setRange(ui->plot->yAxis2->range());
    }
    else if(ui->plot->graph(4)->selected())
    {
        checker.isFit_click = false;
        ui->plot->axisRect()->setRangeDragAxes(ui->plot->xAxis,ui->plot->yAxis);
        ui->plot->yAxis2->setRange(ui->plot->yAxis->range());
    }
    else if(ui->plot->graph(5)->selected())
    {
        checker.isFit_click = false;
        ui->plot->axisRect()->setRangeDragAxes(ui->plot->xAxis,ui->plot->yAxis);
        ui->plot->yAxis2->setRange(ui->plot->yAxis->range());
    }
    else if(ui->plot->graph(6)->selected())
    {
        checker.isFit_click = false;
        ui->plot->axisRect()->setRangeDragAxes(ui->plot->xAxis,ui->plot->yAxis2);
        ui->plot->yAxis->setRange(ui->plot->yAxis2->range());
    }
    else if(ui->plot->graph(7)->selected())
    {
        checker.isFit_click = false;
        ui->plot->axisRect()->setRangeDragAxes(ui->plot->xAxis,ui->plot->yAxis2);
        ui->plot->yAxis->setRange(ui->plot->yAxis2->range());
    }
    else
    {
        ui->plot->axisRect()->setRangeDrag(0);
    }
}

void MainWindow::on_FIT_BTN_clicked()
{
    checker.isFit_click = true;
    ui->plot->xAxis->setRange(0,plotMaxMin.sec_max);
    ui->plot->yAxis->setRange(range_min-25,range_max+25);//ต้อง เอา rangemax , rangemin บันทึกใน Savefile
    ui->plot->yAxis2->setRange(range_min-25,range_max+25);//
    ui->plot->replot();
}

void MainWindow::on_ZOOM_IN_BTN_clicked()
{
    checker.isFit_click = false;

}

void MainWindow::on_ZOOM_OUT_BTN_clicked()
{
    checker.isFit_click = false;

}
