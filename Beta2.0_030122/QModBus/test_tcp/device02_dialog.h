#ifndef DEVICE02_DIALOG_H
#define DEVICE02_DIALOG_H

#include <QDialog>
#include "qmodbus.h"
namespace Ui {
class Device02_dialog;
}

class Device02_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Device02_dialog(QWidget *parent = nullptr);
    ~Device02_dialog();

    QString IPV4_Selected();
    QString Slave_Selected();
    QString Port_Selected();
    QString Reg_Selected();
    QString Count_Selected();

public slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Device02_dialog *ui;

    QModBus_TCP  device02_mbTCP;
    void IPV4_init();
    void Slave_init();
    void Port_init();
    void Reg_init();
    void Count_init();
};

#endif // DEVICE02_DIALOG_H
