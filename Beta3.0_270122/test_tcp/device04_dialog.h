#ifndef DEVICE04_DIALOG_H
#define DEVICE04_DIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "qmodbus.h"
namespace Ui {
class Device04_dialog;
}

class Device04_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Device04_dialog(QWidget *parent = nullptr);
    ~Device04_dialog();

    QString ComPort_Selected();
    QString BuadRate_Selected();
    QString Parity_Selected();
    QString DataBits_Selected();
    QString StopBit_Selected();
    QString Slave_Selected();
    QString Reg_Selected();
    QString Count_Selected();

    QString OkBTN();  //check ว่ากดปุ่ม OK หรือ Cancel
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Device04_dialog *ui;

    void AllComboBoxItemLoad();
    void ComPort_Init();
    void Slave_init();
    void BuadRate_Init();
    void Parity_Init();
    void DataBits_Init();
    void StopBit_Init();

    void Reg_init();
    void Count_init();

    QString status_button_state;  //check ว่ากดปุ่ม OK หรือ Cancel

    QModBus_RTU device04_mbRTU;

    uint16_t  rd_buf_device04[MODBUS_MAX_READ_REGISTERS];
};

#endif // DEVICE04_DIALOG_H
