#ifndef DEVICE04_DIALOG_H
#define DEVICE04_DIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "qmodbus.h"
#include "property_rtu_dv4.h"

namespace Ui {
class Device04_dialog;
}

class Device04_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Device04_dialog(QWidget *parent = nullptr);
    ~Device04_dialog();

    QString ComPort_Selected();     //Before fix
    QString BuadRate_Selected();    //Before fix
    QString Parity_Selected();      //Before fix
    QString DataBits_Selected();    //Before fix
    QString StopBit_Selected();     //Before fix
    QString Slave_Selected();       //Before fix
    QString Reg_Selected();         //Before fix
    QString Count_Selected();       //Before fix

    QString OkBTN();  //check ว่ากดปุ่ม OK หรือ Cancel

    Property_RTU_DV4 rtu() const;                   //ใช้
    void setRtu(const Property_RTU_DV4 &rtu);       //ใช้ เก็บค่าที่ตั้งไว้

private slots:
    void on_buttonBox_accepted();                   //ใช้

    void on_buttonBox_rejected();                   //ใช้

private:
    Ui::Device04_dialog *ui;

    void AllComboBoxItemLoad();     //Before fix    //ใช้
    void ComPort_Init();            //Before fix
    void Slave_init();              //Before fix
    void BuadRate_Init();           //Before fix
    void Parity_Init();             //Before fix
    void DataBits_Init();           //Before fix
    void StopBit_Init();            //Before fix

    void Reg_init();                //Before fix
    void Count_init();              //Before fix

    QString status_button_state;  //check ว่ากดปุ่ม OK หรือ Cancel

    QModBus_RTU device04_mbRTU;     //Before fix

    uint16_t  rd_buf_device04[MODBUS_MAX_READ_REGISTERS];

    Property_RTU_DV4 m_rtu;                         //ใช้

};

#endif // DEVICE04_DIALOG_H
