#ifndef DEVICE02_TCP_H
#define DEVICE02_TCP_H
#include "device02_dialog.h"
#include "qmodbus.h"
#include <QMessageBox>
#include <QObject>

class Device02_TCP
{

public:
    //explicit Device02_TCP(QObject *parent = 0);
    Device02_TCP();
    //QModBus_TCP  device02_mbTCP;
    Device02_dialog *device02_dialog;
public slots:

    //void connect_btn_clicked(); /*เดิม*/
    void connect_to_dev();      /*เดิม*/
    void disconnect_from_dev(); /*เดิม*/

    void read_regs();   /*เดิม*/
    //void write_reg();   /*เดิม*/

    void response_to_read_regs(int status); /*เดิม*/
    //void response_to_write_reg(int status); /*เดิม*/

    void process_error(QModBus::ModBusError error); /*เดิม*/
    void change_status();   /*เดิม*/

    void device02_dialog_exec();
    
private:

    QModBus_TCP  device02_mbTCP;    /*เดิม*/

    uint16_t  rd_buf[MODBUS_MAX_READ_REGISTERS];    /*เดิม*/
    
    //Device02_dialog *device02_dialog;
};

#endif // DEVICE02_TCP_H
