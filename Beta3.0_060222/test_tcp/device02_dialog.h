#ifndef DEVICE02_DIALOG_H
#define DEVICE02_DIALOG_H

#include <QDialog>
#include "qmodbus.h"
#include "property_tcp_dv2.h"

namespace Ui {
class Device02_dialog;
}

class Device02_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Device02_dialog(QWidget *parent = nullptr);
    ~Device02_dialog();

    QString IPV4_Selected();        //Before fix
    QString Slave_Selected();       //Before fix
    QString Port_Selected();        //Before fix
    QString Reg_Selected();         //Before fix
    QString Count_Selected();       //Before fix
    QString OkBTN();                //Before fix

    Property_TCP_DV2 tcp() const;
    void setTcp(const Property_TCP_DV2 &tcp);

public slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Device02_dialog *ui;

    QModBus_TCP  device02_mbTCP;    //Before fix

    QString status_button_state;    //Before fix

    void IPV4_init();               //Before fix
    void Slave_init();              //Before fix
    void Port_init();               //Before fix
    void Reg_init();                //Before fix
    void Count_init();              //Before fix

    Property_TCP_DV2 m_tcp;
};

#endif // DEVICE02_DIALOG_H
