#include "mainwindow.h"
#include "ui_mainwindow.h"



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



    QObject::connect(ui->connect_button, SIGNAL(clicked()),
                     this,  SLOT(connect_btn_clicked()));   /*เดิม*/



    //read button
    QObject::connect(ui->rd_button, SIGNAL(clicked()),
                     this, SLOT(read_regs()));  /*เดิม*/


    QObject::connect(&mb,  SIGNAL(response_to_read_regs(int)),
                     this, SLOT(response_to_read_regs(int)));   /*เดิม*/



    //write button
    QObject::connect(ui->wr_button, SIGNAL(clicked()),
                     this, SLOT(write_reg()));  /*เดิม*/


    QObject::connect(&mb,  SIGNAL(response_to_write_reg(int)),
                     this, SLOT(response_to_write_reg(int)));   /*เดิม*/

    connect(ui->actionDevice1,&QAction::triggered,
            this,&MainWindow::device01_dialog_exec);

    connect(ui->actionMODBUS_TCP,&QAction::triggered,
            this,&MainWindow::device02_dialog_exec);

    serial.setPortName("COM3");
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
    }
    //Device01_Property_Set();

    //connect(&serial,&QSerialPort::readyRead,this,&MainWindow::readData);
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

        return;
    }

    if( count <= 0)
    {
        ui->log_plain_text_edit->appendPlainText(QString("Error count reg is: %1").arg(count));
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
}

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
