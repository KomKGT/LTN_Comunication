#ifndef DEVICE01_DIALOG_H
#define DEVICE01_DIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSettings>
#include <QMessageBox>
namespace Ui {
class Device01_Dialog;
}

class Device01_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Device01_Dialog(QWidget *parent = nullptr);
    ~Device01_Dialog();

    QString ComPort_Selected();
    QString BuadRate_Selected();
    QString DataBits_Selected();
    QString StopBit_Selected();
    QString Parity_Selected();
private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Device01_Dialog *ui;

    void AllComboBoxItemLoad();

    void Load_Init();

    void ComPort_Init();
    void BuadRate_Init();
    void DataBits_Init();
    void StopBit_Init();
    void Parity_Init();
};

#endif // DEVICE01_DIALOG_H
