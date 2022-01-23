#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


QSerialPort serial;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QObject::connect(&mb,  SIGNAL(error(QModBus::ModBusError)),
                     this, SLOT(process_error(QModBus::ModBusError)));  /*เดิม*/



    QObject::connect(&mb,  SIGNAL(connected()),
                     this, SLOT(change_status()));  /*เดิม*/

    QObject::connect(&mb,  SIGNAL(disconnected()),
                     this, SLOT(change_status()));  /*เดิม*/
/***********************************************************************************************/
    QObject::connect(&device02_mbTCP,  SIGNAL(error(QModBus::ModBusError)),
                     this, SLOT(device02_process_error(QModBus::ModBusError)));  //dv2


    QObject::connect(&device02_mbTCP,  SIGNAL(connected()),
                     this, SLOT(device02_change_status()));  //dv2

    QObject::connect(&device02_mbTCP,  SIGNAL(disconnected()),
                     this, SLOT(device02_change_status()));  //dv2

    QObject::connect(&device02_mbTCP,&QModBus::response_to_read_regs,
                     this,&MainWindow::device02_response_to_read_regs);   //dv2

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()),
                     this, SLOT(device02_read_regs()));  //dv2

/***********************************************************************************************/
    QObject::connect(&device03_mbTCP,  SIGNAL(error(QModBus::ModBusError)),
                     this, SLOT(device03_process_error(QModBus::ModBusError)));  //dv3


    QObject::connect(&device03_mbTCP,  SIGNAL(connected()),
                     this, SLOT(device03_change_status()));  //dv3

    QObject::connect(&device03_mbTCP,  SIGNAL(disconnected()),
                     this, SLOT(device03_change_status()));  //dv3

    QObject::connect(&device03_mbTCP,&QModBus::response_to_read_regs,
                     this,&MainWindow::device03_response_to_read_regs);   //dv3

    timer3 = new QTimer(this);
    QObject::connect(timer3, SIGNAL(timeout()),
                     this, SLOT(device03_read_regs()));  //dv3
/***********************************************************************************************/
    QObject::connect(&device04_mbRTU,  SIGNAL(error(QModBus::ModBusError)),
                     this, SLOT(device04_process_error(QModBus::ModBusError)));

    QObject::connect(&device04_mbRTU,  SIGNAL(connected()),
                     this, SLOT(device04_change_status()));

    QObject::connect(&device04_mbRTU,  SIGNAL(disconnected()),
                     this, SLOT(device04_change_status()));

    QObject::connect(&device04_mbRTU,&QModBus::response_to_read_regs,
                     this,&MainWindow::device04_response_to_read_regs);

    timer4 = new QTimer(this);
    QObject::connect(timer4, SIGNAL(timeout()),
                     this, SLOT(device04_read_regs()));
/***********************************************************************************************/
    QObject::connect(ui->connect_button, SIGNAL(clicked()),
                     this,  SLOT(connect_btn_clicked()));   /*เดิม*/



    //read button
    QObject::connect(ui->rd_button, SIGNAL(clicked()),
                     this, SLOT(read_regs()));  /*เดิม*/


    QObject::connect(&mb,&QModBus::response_to_read_regs,
                     this,&MainWindow::response_to_read_regs);   /*เดิม*/

    //QObject::connect(&mb,  SIGNAL(response_to_read_regs(int)),
                     //this, SLOT(response_to_read_regs(int)));   /*เดิม*/

    //write button
    QObject::connect(ui->wr_button, SIGNAL(clicked()),
                     this, SLOT(write_reg()));  /*เดิม*/


    QObject::connect(&mb,  SIGNAL(response_to_write_reg(int)),
                     this, SLOT(response_to_write_reg(int)));   /*เดิม*/

    //connect(&device02_dialog,&Device02_dialog::on_buttonBox_accepted,
            //device,&Device02_TCP::connect_to_dev);

    connect(ui->actionDevice1,&QAction::triggered,
            this,&MainWindow::device01_dialog_exec);    /*Device01 Normal Serialport*/

    connect(ui->actionMODBUS_TCP,&QAction::triggered,
            this,&MainWindow::device02_dialog_exec);    /*Device02 TCP*/

    connect(ui->actionMODBUS_TCP_3,&QAction::triggered,
            this,&MainWindow::device03_dialog_exec);

    connect(ui->actionMODBUS_RTU,&QAction::triggered,
            this,&MainWindow::device04_dialog_exec);    /*Device04 RTU*/


    /*serial.setPortName("COM3");
    serial.setBaudRate(serial.Baud9600);
    serial.setDataBits(serial.Data8);
    serial.setStopBits(serial.OneStop);
    serial.setParity(serial.NoParity);
    serial.setFlowControl(serial.NoFlowControl);
    if(serial.open(QIODevice::ReadWrite))
    {
        ui->textEdit->append("Open Port Success\r\n");
    }
    else{
        ui->textEdit->append("Unable to open Com Port");
    }*/
    //Device01_Property_Set();

    //connect(&serial,&QSerialPort::readyRead,this,&MainWindow::readData);
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



void MainWindow::connect_btn_clicked()
{
    if( mb.is_connected() )
        disconnect_from_dev();
    else
        connect_to_dev();
}



void MainWindow::connect_to_dev()
{

    ui->connect_button->setEnabled(false);


    //GUI param to QModBus_TCP object
    mb.IP    = ui->IPv4_line_edit->text();
    mb.port  = ui->port_line_edit->text().toInt();
    mb.set_slave(ui->slave_line_edit->text().toInt());

    //show param in Edit
    ui->log_plain_text_edit->appendPlainText(QString("###############################"));
    ui->log_plain_text_edit->appendPlainText(QString("IPv4  is: %1").arg(mb.IP));
    ui->log_plain_text_edit->appendPlainText(QString("Port  is: %1").arg(mb.port));
    ui->log_plain_text_edit->appendPlainText(QString("Slave is: %1").arg(mb.get_slave()));
    ui->log_plain_text_edit->appendPlainText(QString("-------------------------------"));


    mb.connect();
}



void MainWindow::disconnect_from_dev()
{
    ui->connect_button->setEnabled(false);
    mb.disconnect();
}



void MainWindow::read_regs()
{

    int addr  = ui->rd_reg_line_edit->text().toInt();
    int count = ui->rd_count_line_edit->text().toInt();

    if( count > MODBUS_MAX_READ_REGISTERS)
    {
        ui->log_plain_text_edit->appendPlainText(QString("Error count reg is: %1").arg(count));
        ui->log_plain_text_edit->insertPlainText(QString("Max count reg is: %1").arg(MODBUS_MAX_READ_REGISTERS));
        //QMessageBox::warning(NULL,"Error Register",QString("Error count reg is: %1 Max count reg is: %2").arg(count).arg(MODBUS_MAX_READ_REGISTERS));
        return;
    }

    if( count <= 0)
    {
        ui->log_plain_text_edit->appendPlainText(QString("Error count reg is: %1").arg(count));
        QMessageBox::critical(NULL,"Error Register",QString("Error count reg is: %1").arg(count));
        //QMessageBox::warning(NULL,"Error Register",QString("Error count reg is: %1 Max count reg is: %2").arg(count).arg(MODBUS_MAX_READ_REGISTERS));
        return;
    }


    ui->log_plain_text_edit->appendPlainText(QString("Read Start register: %1 ").arg(addr));
    ui->log_plain_text_edit->insertPlainText(QString("Count: %1").arg(count));

    ui->rd_button->setEnabled(false);

    mb.read_regs(addr, count, rd_buf);
}



void MainWindow::write_reg()
{
    int addr  = ui->wr_reg_line_edit->text().toInt();
    int value = ui->wr_val_line_edit->text().toInt();


    ui->log_plain_text_edit->appendPlainText(QString("Write to register: %1 ").arg(addr));
    ui->log_plain_text_edit->insertPlainText(QString("value: %1").arg(value));

    ui->wr_button->setEnabled(false);

    mb.write_reg(addr, value);
}



void MainWindow::response_to_read_regs(int status)
{
    int i;

    ui->rd_button->setEnabled(true);


    ui->log_plain_text_edit->appendPlainText(QString("Read status: %1").arg(status));


    if( status <= 0 )
        return;


    ui->log_plain_text_edit->appendPlainText(QString("Reading regs: %1").arg(status));

    for(i = 0; i < status; i++)
    {
        ui->log_plain_text_edit->appendPlainText(QString("reg[%1] == %2").arg(i).arg(rd_buf[i]));
    }
}



void MainWindow::response_to_write_reg(int status)
{
    ui->wr_button->setEnabled(true);

    ui->log_plain_text_edit->appendPlainText(QString("Write status: %1").arg(status));
}



void MainWindow::process_error(QModBus::ModBusError error)
{
    //show error in Edit
    ui->log_plain_text_edit->appendPlainText(QString("Error is: %1  strerror: ").arg(error));
    ui->log_plain_text_edit->insertPlainText(QString::fromUtf8(mb.get_strerror()));


    switch (error)
    {

        case QModBus::NoConnectionError:
        case QModBus::CreateError:
        case QModBus::ConnectionError:
        {
            ui->connect_button->setEnabled(true);
            //timer->stop();
            break;
        }


        case QModBus::ReadRegsError:
        {
            ui->rd_button->setEnabled(true);
            break;
        }


        case QModBus::WriteRegError:
        {
            ui->wr_button->setEnabled(true);
            break;
        }


        default:
            break;
    }

}



void MainWindow::change_status()
{

    ui->connect_button->setEnabled(true);


    if( mb.is_connected() )
    {
        ui->log_plain_text_edit->appendPlainText("------ connected ------");
        ui->connect_button->setText("Disconnect");
        return;
    }


    ui->log_plain_text_edit->appendPlainText("------ disconnected ------\n");
    ui->connect_button->setText("Connect");
}
/******************************************************************************************************************/
void MainWindow::device02_connect_to_dev()
{
    device02_mbTCP.IP = device02_dialog->IPV4_Selected();
    device02_mbTCP.port = device02_dialog->Port_Selected().toInt();
    device02_mbTCP.set_slave(device02_dialog->Slave_Selected().toInt());

    device02_mbTCP.connect();



}

void MainWindow::device02_disconnect_from_dev()
{
    device02_mbTCP.disconnect();
}

void MainWindow::device02_read_regs()
{
    int addr = device02_dialog->Reg_Selected().toInt();
    int count = device02_dialog->Count_Selected().toInt();

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
            ui->lcdNumber->display(rd_buf_device02[i]);//แสดงบน ui
        }
        else if(i==1)
        {
            ui->lcdNumber_2->display(rd_buf_device02[i]);//แสดงบน ui
        }
        else if(i==2)
        {
            ui->lcdNumber_3->display(rd_buf_device02[i]);//แสดงบน ui
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
    device04_mbRTU.device = device04_dialog->ComPort_Selected();
    device04_mbRTU.baudrate = device04_dialog->BuadRate_Selected().toInt();
    device04_mbRTU.parity = device04_dialog->Parity_Selected().at(0).toLatin1();
    device04_mbRTU.data_bit = device04_dialog->DataBits_Selected().toInt();
    device04_mbRTU.stop_bit = device04_dialog->StopBit_Selected().toInt();
    device04_mbRTU.set_slave(device04_dialog->Slave_Selected().toInt());

    device04_mbRTU.connect();


}

void MainWindow::device04_disconnect_from_dev()
{
    device04_mbRTU.disconnect();
}

void MainWindow::device04_read_regs()
{
    int addr = device04_dialog->Reg_Selected().toInt();
    int count = device04_dialog->Count_Selected().toInt();

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
            ui->lcdNumber_4->display(rd_buf_device04[i]);//แสดงบน ui
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
/**************************************************************************************************************/
void MainWindow::device01_dialog_exec()
{
    device01_dialog = new Device01_Dialog(this);
    device01_dialog->exec();

    Device01_Property_Set();
}

void MainWindow::device02_dialog_exec()
{
    device02_dialog = new Device02_dialog(this);
    device02_dialog->exec();

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
}

void MainWindow::device03_dialog_exec()
{
    device03_dialog = new Device03_Dialog(this);
    device03_dialog->exec();
}

void MainWindow::device04_dialog_exec()
{
    device04_dialog = new Device04_dialog(this);
    device04_dialog->exec();

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
}
/*****************************************************************/
void MainWindow::readData()
{
    QByteArray data = serial.readAll();
    ui->textEdit->insertPlainText(QString(data));
}

void MainWindow::ComPort_Set()
{
    serial.setPortName(device01_dialog->ComPort_Selected());
}

void MainWindow::BuadRate_Set()
{
    if(device01_dialog->BuadRate_Selected()=="1200")
        serial.setBaudRate(serial.Baud1200);
    else if(device01_dialog->BuadRate_Selected()=="2400")
        serial.setBaudRate(serial.Baud2400);
    else if(device01_dialog->BuadRate_Selected()=="4800")
        serial.setBaudRate(serial.Baud4800);
    else if(device01_dialog->BuadRate_Selected()=="9600")
        serial.setBaudRate(serial.Baud9600);
    else if(device01_dialog->BuadRate_Selected()=="19200")
        serial.setBaudRate(serial.Baud19200);
    else if(device01_dialog->BuadRate_Selected()=="38400")
        serial.setBaudRate(serial.Baud38400);
    else if(device01_dialog->BuadRate_Selected()=="57600")
        serial.setBaudRate(serial.Baud57600);
    else if(device01_dialog->BuadRate_Selected()=="115200")
        serial.setBaudRate(serial.Baud115200);
}

void MainWindow::DataBits_Set()
{
    if(device01_dialog->DataBits_Selected()=="5")
        serial.setDataBits(serial.Data5);
    else if(device01_dialog->DataBits_Selected()=="6")
        serial.setDataBits(serial.Data6);
    else if(device01_dialog->DataBits_Selected()=="7")
        serial.setDataBits(serial.Data7);
    else if(device01_dialog->DataBits_Selected()=="8")
        serial.setDataBits(serial.Data8);
}

void MainWindow::StopBit_Set()
{
    if(device01_dialog->StopBit_Selected()=="1")
        serial.setStopBits(serial.OneStop);
    else if(device01_dialog->StopBit_Selected()=="1.5")
        serial.setStopBits(serial.OneAndHalfStop);
    else if(device01_dialog->StopBit_Selected()=="2")
        serial.setStopBits(serial.TwoStop);
}

void MainWindow::Parity_Set()
{
    if(device01_dialog->Parity_Selected()=="NoParity")
        serial.setParity(serial.NoParity);
    else if(device01_dialog->Parity_Selected()=="OddParity")
        serial.setParity(serial.OddParity);
    else if(device01_dialog->Parity_Selected()=="EvenParity")
        serial.setParity(serial.EvenParity);
    else if(device01_dialog->Parity_Selected()=="MarkParity")
        serial.setParity(serial.MarkParity);
    else if(device01_dialog->Parity_Selected()=="SpaceParity")
        serial.setParity(serial.SpaceParity);
}

void MainWindow::Device01_Property_Set()
{
    ComPort_Set();
    BuadRate_Set();
    DataBits_Set();
    StopBit_Set();
    Parity_Set();
    serial.setFlowControl(serial.NoFlowControl);
    if(serial.open(QIODevice::ReadWrite))
    {
        ui->textEdit->append("Open Port Success\r\n");
    }
    else{
        ui->textEdit->append("Unable to open Com Port");
    }
}
/*****************************************************************/
