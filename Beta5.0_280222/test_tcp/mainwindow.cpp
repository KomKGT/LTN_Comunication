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



/***********************************************************************************************/
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

/***********************************************************************************************/
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
/***********************************************************************************************/
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
/***********************************************************************************************/


/****************************** ACTION SECTION ********************************************/
    connect(ui->actionDevice1,&QAction::triggered,
            this,&MainWindow::device01_dialog_exec);    /*Device01 Normal Serialport*/

    connect(ui->actionMODBUS_TCP,&QAction::triggered,
            this,&MainWindow::device02_dialog_exec);    /*Device02 TCP*/

    connect(ui->actionMODBUS_TCP_3,&QAction::triggered, /*Device03 TCP UNUSE*/
            this,&MainWindow::device03_dialog_exec);

    connect(ui->actionMODBUS_RTU,&QAction::triggered,
            this,&MainWindow::device04_dialog_exec);    /*Device04 RTU*/

    connect(ui->actionOpen_File,&QAction::triggered,
            this,&MainWindow::openFile_dialog_exec);


    QPalette Pal = ui->lcdNumber->palette();
    Pal.setColor(QPalette::Normal,QPalette::WindowText,Qt::green);
    Pal.setColor(QPalette::Normal, QPalette::Window, Qt::black);
    ui->lcdNumber->setPalette(Pal);
    ui->lcdNumber->display("0");

    device04_mbRTU.disconnect();


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
    }
    else{
        //ui->textEdit->append("Unable to open Com Port");
         qDebug()<<"Open Port NotSuccess\r\n";
    }
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
        QMessageBox::warning(NULL,"Error Register",QString("Error count reg is: %1 Max count reg is: %2").arg(count).arg(MODBUS_MAX_READ_REGISTERS));
        return;
    }
    if(count <= 0)
    {
        QMessageBox::warning(NULL,"Error Register",QString("Error count reg is: %1").arg(count));
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
            ui->lcdNumber->display(rd_buf_device02[i]);//?????????????????? ui
        }
        else if(i==1)
        {
            ui->lcdNumber_2->display(rd_buf_device02[i]);//?????????????????? ui
        }
        else if(i==2)
        {
            ui->lcdNumber_3->display(rd_buf_device02[i]);//?????????????????? ui
        }
        //ui->log_plain_text_edit->appendPlainText(QString("reg[%1] == %2").arg(i).arg(rd_buf_device02[i]));
    }
}

void MainWindow::device02_process_error(QModBus::ModBusError error)
{
    timer->stop();//????????????????????????????????? QMessageBox ??????????????????????????????????????????????????? error
    switch (error)
    {

        case QModBus::NoConnectionError:
        case QModBus::CreateError:
        case QModBus::ConnectionError:
        {
            QMessageBox::critical(NULL,"ERROR","Connection Error or Create Error");
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
            QMessageBox::critical(NULL,"ERROR","Write Register Error");
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
        QMessageBox::warning(NULL,"Error Register",QString("Error count reg is: %1 Max count reg is: %2").arg(count).arg(MODBUS_MAX_READ_REGISTERS));
        return;
    }
    if(count <= 0)
    {
        QMessageBox::warning(NULL,"Error Register",QString("Error count reg is: %1").arg(count));
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
            //ui->lcdNumber->display(rd_buf_device03[i]);//?????????????????? ui
        }
        else if(i==1)
        {
            //ui->lcdNumber_2->display(rd_buf_device03[i]);//?????????????????? ui
        }
        else if(i==2)
        {
            //ui->lcdNumber_3->display(rd_buf_device03[i]);//?????????????????? ui
        }
        //ui->log_plain_text_edit->appendPlainText(QString("reg[%1] == %2").arg(i).arg(rd_buf_device02[i]));
    }
}

void MainWindow::device03_process_error(QModBus::ModBusError error)
{
    timer3->stop();//????????????????????????????????? QMessageBox ??????????????????????????????????????????????????? error
    switch (error)
    {

        case QModBus::NoConnectionError:
        case QModBus::CreateError:
        case QModBus::ConnectionError:
        {
            QMessageBox::critical(NULL,"ERROR","Device3 Connection Error or Create Error");
            break;
        }


        case QModBus::ReadRegsError:
        {
            QMessageBox::critical(this,"ERROR","Device3 Read Register Error");
            break;
        }


        case QModBus::WriteRegError:
        {
            QMessageBox::critical(NULL,"ERROR","Device3 Write Register Error");
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
        QMessageBox::warning(NULL,"Device04 Error Register",QString("Error count reg is: %1 Max count reg is: %2").arg(count).arg(MODBUS_MAX_READ_REGISTERS));
        return;
    }
    if(count <= 0)
    {
        QMessageBox::warning(NULL,"Device04 Error Register",QString("Error count reg is: %1").arg(count));
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
            ui->lcdNumber_4->display(rd_buf_device04[i]);//?????????????????? ui
        }
        else if(i==1)
        {
            //ui->lcdNumber_2->display(rd_buf_device03[i]);//?????????????????? ui
        }
        else if(i==2)
        {
            //ui->lcdNumber_3->display(rd_buf_device03[i]);//?????????????????? ui
        }
        //ui->log_plain_text_edit->appendPlainText(QString("reg[%1] == %2").arg(i).arg(rd_buf_device02[i]));
    }
}

void MainWindow::device04_process_error(QModBus::ModBusError error)
{
    timer4->stop();//????????????????????????????????? QMessageBox ??????????????????????????????????????????????????? error
    switch (error)
    {

        case QModBus::NoConnectionError:
        case QModBus::CreateError:
        case QModBus::ConnectionError:
        {
            QMessageBox::critical(NULL,"Device4 ERROR","Connection Error or Create Error");
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
            QMessageBox::critical(NULL,"Device4 ERROR","Write Register Error");
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

void MainWindow::openFile_dialog_exec()
{
    QString filter = "Text Files (*.csv)";
    QString file_name = QFileDialog::getOpenFileName(this,"Open a file",QDir::homePath(),filter);
    QMessageBox::information(this,"Selected",file_name);


    QFile inputFile(file_name);
    if(inputFile.open(QIODevice::ReadOnly))
    {
        v_x.clear();
        v_y.clear();
        qv_x.clear();
        qv_y.clear();
        ui->plot->addGraph();
        ui->plot->graph(0)->data().data()->clear();
        ui->plot->replot();
        QTextStream in(&inputFile);
        int count = 0;
        QString x;
        QString y;
        while(!in.atEnd())
        {
            if(count<1)         //????????????????????????????????????????????????????????? count = 0
            {
                QString line0 = in.readLine();
            }
            else if(count >= 1) //????????????????????????????????????????????????????????? count = 0
            {
                QStringList items = in.readLine().split(',');
                x = items.at(0);    //?????????????????????????????????????????????????????? comma ?????????????????? x
                y = items.at(1);    //?????????????????????????????????????????????????????? comma ?????????????????? x
                str_x[count] = x;
                str_y[count] = y;
                v_x.push_back(str_x[count].toDouble());
                v_y.push_back(str_y[count].toDouble());
            }
            count++;
        }
        inputFile.close();

        double max_x = *max_element(v_x.begin(), v_x.end());
        double max_y = *max_element(v_y.begin(), v_y.end());

        ui->plot->xAxis->setRange(0,max_x); //max_x ?????????????????????????????????????????????????????? x ???????????????????????????
        ui->plot->yAxis->setRange(0,max_y); //max_???y ?????????????????????????????????????????????????????? y ???????????????????????????
        for(int i = 1;i<=v_x.size();i++)    //????????????????????????????????????????????????????????? count = 0
        {
            qv_x.append(str_x[i].toDouble());
            qv_y.append(str_y[i].toDouble());
            ui->plot->graph(0)->setData(qv_x,qv_y);
            ui->plot->replot();
        }
    }
}
/**************************************************************************************************************/
void MainWindow::device01_dialog_exec()
{
    device01_dialog = new Device01_Dialog(this);
    device01_dialog->setSerialport(m_serialport);
    device01_dialog->exec();


    m_serialport = device01_dialog->serialport();
    if(device01_dialog->OkBTN()=="OK") //check ????????? device02_dialog ?????? OK ???????????? CANCEL ?????????????????????????????????????????????????????? Qmessagebox connected
    {
        device01_connect_to_dev();


    }
    else if(device01_dialog->OkBTN()=="CANCEL")
    {


    }
}

void MainWindow::device02_dialog_exec()
{
    device02_dialog = new Device02_dialog(this);
    device02_dialog->setTcp(m_tcp);
    device02_dialog->exec();

    m_tcp = device02_dialog->tcp();
    if(device02_dialog->OkBTN()=="OK") //check ????????? device02_dialog ?????? OK ???????????? CANCEL ?????????????????????????????????????????????????????? Qmessagebox connected
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
    if(device04_dialog->OkBTN()=="OK") //check ????????? device02_dialog ?????? OK ???????????? CANCEL
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
/*****************************************************************/







/*****************************************************************/
