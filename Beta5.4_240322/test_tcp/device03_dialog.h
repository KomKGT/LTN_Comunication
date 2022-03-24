#ifndef DEVICE03_DIALOG_H
#define DEVICE03_DIALOG_H

#include <QDialog>

namespace Ui {
class Device03_Dialog;
}

class Device03_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Device03_Dialog(QWidget *parent = nullptr);
    ~Device03_Dialog();


    QString IPV4_Selected();
    QString Slave_Selected();
    QString Port_Selected();
    QString Reg_Selected();
    QString Count_Selected();



private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Device03_Dialog *ui;

    //QModBus_TCP  device02_mbTCP;
    void IPV4_init();
    void Slave_init();
    void Port_init();
    void Reg_init();
    void Count_init();
};

#endif // DEVICE03_DIALOG_H
