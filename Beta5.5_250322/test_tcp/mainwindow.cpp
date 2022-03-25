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
        P2 = SplitCode(item,&A,&B).toDouble()/10;
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
    v_y2.push_back(T2); //เอา Tstart = v_y2[0],Tend เอาค่าสุดท้าย,Tmax and Tmin เอา vector มาเรียง
    double T2_max = *max_element(v_y2.begin(), v_y2.end());
    double T2_min = *min_element(v_y2.begin(), v_y2.end());
    v_y3.push_back(T1); //เอา Tstart = v_y3[0],Tend เอาค่าสุดท้าย

    QString Pstart = QString::number(v_y1.at(0));
    QString Pmax = QString::number(P2_max);
    QString DelP = QString::number(P2_max-v_y1.at(0));
    QString FPV = QString::number((P2_max-v_y1.at(0))/ui->PigmentWeight_LE->text().toDouble());
    //QString Pend = QString::number(v_y1.back());
    ui->PStart_LE->setText(Pstart);
    ui->PMax_LE->setText(Pmax);
    ui->DelP_LE->setText(DelP);
    ui->FPV_LE->setText(FPV);

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
        //ui->plot->addGraph();
        ui->plot->graph(0)->data().data()->clear();
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
        //ui->plot->addGraph();
        ui->plot->graph(0)->data().data()->clear();
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
                Sample_ID = items.at(0);
                Base_polymer = items.at(1);
                Customer  = items.at(2);
                Date = items.at(3);
                Operator = items.at(4);
                Filter_screen_size = items.at(5);
                Pigment_weight = items.at(6);
                Total_weight = items.at(7);

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
                v_x.push_back(items.at(0).toDouble());
                v_y.push_back(items.at(1).toDouble());
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

        double max_x = *max_element(v_x.begin(), v_x.end());
        double max_y = *max_element(v_y.begin(), v_y.end());
        double min_y = *min_element(v_y.begin(), v_y.end());
        ui->plot->xAxis->setRange(0,max_x); //max_x คือค่ามากสุดที่แกน x จะโชว์ได้
        ui->plot->yAxis->setRange(min_y,max_y); //max_ัy คือค่ามากสุดที่แกน y จะโชว์ได้
        for(int i = 0;i<v_x.size();i++)    //ไม่สนใจบรรทัดแรกคือ count = 0
        {
            qv_x.append(v_x.at(i));
            qv_y.append(v_y.at(i));
            ui->plot->graph(0)->setData(qv_x,qv_y);
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

    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        //QTextStream out(&file);
        QTextStream out(&file);
        QString newline = "\n";

        /*Save Data from Line Edit*/
        out <<Sample_ID<<","<<Base_polymer<<","<<Customer<<","<<Date<<","<<Operator<<","<<Filter_screen_size<<","<<Pigment_weight<<","<<Total_weight<<"\n"<<"\n"<<"x,y"; //<<"\n"<<"1,2"<<"\n"<<"2,2"<<"\n"<<"3,9"<<"\n"<<"4,50";
        /*End Save Data from Line Edit*/

        /*Plot Graph ถ้าโปรแกรมจริงไม่ต้องใช้*/
        for (int i = 0;i<300;i++)
        {
                out << newline;
                out << i <<","<<10*i*i;
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
        out <<Sample_ID<<","<<Base_polymer<<","<<Customer<<","<<Date<<","<<Operator<<","<<Filter_screen_size<<","<<Pigment_weight<<","<<Total_weight<<"\n"<<"\n"<<"x,y";
        for (int i = 0;i<300;i++)
        {
                out << newline;
                out << i <<","<<10*i*i;
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
                         QMessageBox::Yes|QMessageBox::No);
    if(reply ==QMessageBox::Yes)
    {
        chooseSave();
        //saveFile_dialog();
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
    }

    event->accept();
}

void MainWindow::printPreview()
{
    setStyleSheet("background-color: white;");
    QPrinter printer;
    QPrintPreviewDialog previewDialog(&printer, this);
    previewDialog.resize(1000,1000);

    connect(&previewDialog, SIGNAL(paintRequested(QPrinter*)), SLOT(renderPlot(QPrinter*))); 
    previewDialog.exec();
    setStyleSheet("background-color: light gray;");
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
    pen0.setColor(Qt::red);
    pen0.setWidth(1);
    ui->plot->addGraph();
    ui->plot->graph(0);
    ui->plot->graph(0)->setPen(QPen(pen0));
    ui->plot->graph(0)->setName("Pressure");


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

    ui->plot->addGraph(ui->plot->xAxis,ui->plot->yAxis2);
    //ui->plot->graph(1)->setVisible(false);//ซ่อนกราฟ
    ui->plot->graph(1)->setPen(QPen(Qt::darkYellow));
    ui->plot->graph(1)->setName("Melt temperature");

    ui->plot->addGraph();
    ui->plot->graph(2);
    ui->plot->graph(2)->setPen(QPen(Qt::blue));
    ui->plot->graph(2)->setName("Pressure2");

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
    }
    else if(feedrate_dialog->OkBTN()=="CANCEL")
    {
        ui->actionCC_Min->setChecked(true);
        ui->actionrpm->setChecked(false);
    }

    delete feedrate_dialog;
}

void MainWindow::start_dialog_exec()
{
    start_dialog = new Start_Dialog(this);
    start_dialog->setValue(value);
    start_dialog->exec();
    value = start_dialog->getValue();
    if(start_dialog->okBTN()=="OK")
    {
        if(start_dialog->getValue().getChoose()==false)
        {
            //qDebug()<<"Time = "<<value.getTime().toInt();
            qDebug()<<"Choose "<<value.getChoose();
        }
        else if(start_dialog->getValue().getChoose()==true)
        {
            //qDebug()<<"Time = "<<value.getTime().toInt();
            qDebug()<<"Choose "<<value.getChoose();
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

void MainWindow::on_pushButton_clicked()
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
}

void MainWindow::on_START_BTN_clicked()
{
    start_dialog_exec();
}
