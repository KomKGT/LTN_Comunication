#include "device02_tcp.h"
#include <QDebug>
Device02_TCP::Device02_TCP()
{
    qDebug()<<"Call";
    //connect(&device02_dialog,&Device02_dialog::on_buttonBox_accepted,
            //this,&Device02_TCP::connect_to_dev);
    //QObject::connect(&device02_dialog,&Device02_dialog::on_buttonBox_accepted,
                     //this,&Device02_TCP::connect_to_dev);
}

void Device02_TCP::connect_to_dev()
{
    device02_mbTCP.IP = device02_dialog->IPV4_Selected();
    device02_mbTCP.port = device02_dialog->Port_Selected().toInt();
    device02_mbTCP.set_slave(device02_dialog->Slave_Selected().toInt());

    device02_mbTCP.connect();
}

void Device02_TCP::disconnect_from_dev()
{
    device02_mbTCP.disconnect();
}

void Device02_TCP::read_regs()
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
    device02_mbTCP.read_regs(addr,count,rd_buf);
}

void Device02_TCP::response_to_read_regs(int status)
{
    int i;

    if(status<=0)
        return;
    for(i = 0; i < status; i++)
    {
        if(i==0)
        {
            //แสดงบน ui
        }
        if(i==1)
        {
            //แสดงบน ui
        }
        if(i==2)
        {
            //แสดงบน ui
        }
        //ui->log_plain_text_edit->appendPlainText(QString("reg[%1] == %2").arg(i).arg(rd_buf[i]));
    }
}

void Device02_TCP::process_error(QModBus::ModBusError error)
{
    //show error in Edit
    //ui->log_plain_text_edit->appendPlainText(QString("Error is: %1  strerror: ").arg(error));
    //ui->log_plain_text_edit->insertPlainText(QString::fromUtf8(mb.get_strerror()));


    switch (error)
    {

        case QModBus::NoConnectionError:
        case QModBus::CreateError:
        case QModBus::ConnectionError:
        {
            QMessageBox::critical(NULL,"ERROR","Connection Error or Create Error");
            break;
        }


        case QModBus::ReadRegsError:
        {
            QMessageBox::critical(NULL,"ERROR","Read Register Error");
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

void Device02_TCP::change_status()
{
    if(device02_mbTCP.is_connected())
    {
        QMessageBox::information(NULL,"Device2 Connected","Device2 TCP connected");
        return;
    }

    QMessageBox::warning(NULL,"Device2 Disconnected","Device2 TCP Disconnected");
}
