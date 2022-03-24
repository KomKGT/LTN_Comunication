#ifndef DEVICE01_DIALOG_H
#define DEVICE01_DIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSettings>
#include <QMessageBox>
#include "property_serial_dv1.h"
namespace Ui {
class Device01_Dialog;
}

class Device01_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Device01_Dialog(QWidget *parent = nullptr);
    ~Device01_Dialog();

    QString ComPort_Selected();         //Before fix
    QString BuadRate_Selected();        //Before fix
    QString DataBits_Selected();        //Before fix
    QString StopBit_Selected();         //Before fix
    QString Parity_Selected();          //Before fix
    QString OkBTN();

    Property_SERIAL_DV1 serialport() const;
    void setSerialport(const Property_SERIAL_DV1 &serialport);

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Device01_Dialog *ui;

    void AllComboBoxItemLoad();         //Before fix

    void Load_Init();                   //Before fix

    void ComPort_Init();                //Before fix
    void BuadRate_Init();               //Before fix
    void DataBits_Init();               //Before fix
    void StopBit_Init();                //Before fix
    void Parity_Init();                 //Before fix

    Property_SERIAL_DV1 m_serialport;

    QString status_button_state;
};

#endif // DEVICE01_DIALOG_H
