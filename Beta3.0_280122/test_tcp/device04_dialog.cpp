#include "device04_dialog.h"
#include "ui_device04_dialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QSettings>
Device04_dialog::Device04_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Device04_dialog)
{
    ui->setupUi(this);
    AllComboBoxItemLoad();
    ComPort_Init();
    BuadRate_Init();
    Slave_init();
    Parity_Init();
    DataBits_Init();
    StopBit_Init();
    Reg_init();
    Count_init();

    status_button_state = "CANCEL";
}

Device04_dialog::~Device04_dialog()
{
    delete ui;
}

QString Device04_dialog::ComPort_Selected()
{
    return ui->ComPort_Combobox->currentText();
}

QString Device04_dialog::BuadRate_Selected()
{
    return  ui->baudrate_combo_box->currentText();
}

QString Device04_dialog::Parity_Selected()
{
    return  ui->parity_combo_box->currentText();
}

QString Device04_dialog::DataBits_Selected()
{
    return ui->data_bits_combo_box->currentText();
}

QString Device04_dialog::StopBit_Selected()
{
    return ui->stop_bits_combo_box->currentText();
}

QString Device04_dialog::Slave_Selected()
{
    return ui->slave_line_edit->text();
}

QString Device04_dialog::Reg_Selected()
{
    return ui->Reg_lineEdit->text();
}

QString Device04_dialog::Count_Selected()
{
    return ui->Count_lineEdit->text();
}

QString Device04_dialog::OkBTN()
{
    return status_button_state;
}

void Device04_dialog::on_buttonBox_accepted()
{

    QSettings save_ComPort("Mysoft","MyApp");
    save_ComPort.setValue("save_ComPort",ui->ComPort_Combobox->currentIndex());

    QSettings save_BuadRate("Mysoft","MyApp");
    save_BuadRate.setValue("save_BuadRate",ui->baudrate_combo_box->currentIndex());

    QSettings save_Slave("Mysoft","MyApp");
    // save value from QLineEdit
    QString text_Slave = ui->slave_line_edit->text();
    save_Slave.setValue("save_Slave", text_Slave);

    QSettings save_DataBits("Mysoft","MyApp");
    save_DataBits.setValue("save_DataBits",ui->data_bits_combo_box->currentIndex());

    QSettings save_StopBit("Mysoft","MyApp");
    save_StopBit.setValue("save_StopBit",ui->stop_bits_combo_box->currentIndex());

    QSettings save_Parity("Mysoft","MyApp");
    save_Parity.setValue("save_Parity",ui->parity_combo_box->currentIndex());

    QSettings save_Reg("Mysoft","MyApp");
    // save value from QLineEdit
    QString text_Reg = ui->Reg_lineEdit->text();
    save_Reg.setValue("save_Reg", text_Reg);

    QSettings save_Count("Mysoft","MyApp");
    // save value from QLineEdit
    QString text_Count = ui->Count_lineEdit->text();
    save_Count.setValue("save_Count", text_Count);

    status_button_state = "OK";
    OkBTN();
    accept();
}

void Device04_dialog::on_buttonBox_rejected()
{
    status_button_state = "CANCEL";
    reject();
}

void Device04_dialog::AllComboBoxItemLoad()
{
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        ui->ComPort_Combobox->addItem(info.portName());
    }
}

void Device04_dialog::ComPort_Init()
{
    QSettings save_ComPort("Mysoft","MyApp");
    QVariant value = save_ComPort.value("save_ComPort",0);

    bool ok;
    int index = value.toInt(&ok);

    if(!ok)
    {
        QMessageBox::critical(this,"Loading Error","Error loading selection");
        return;
    }
    if(index < ui->ComPort_Combobox->count())
    {
        ui->ComPort_Combobox->setCurrentIndex(index);
    }
    else
    {
        ui->ComPort_Combobox->setCurrentIndex(0);
    }
}

void Device04_dialog::Slave_init()
{
    QSettings save_Slave("Mysoft","MyApp");
    // restore value of QLineEdit
    QString text = save_Slave.value("save_Slave", "1").toString();
    ui->slave_line_edit->setText(text);
}

void Device04_dialog::BuadRate_Init()
{
    QSettings save_BuadRate("Mysoft","MyApp");
    QVariant value = save_BuadRate.value("save_BuadRate",0);

    bool ok;
    int index = value.toInt(&ok);

    if(!ok)
    {
        QMessageBox::critical(this,"Loading Error","Error loading selection");
        return;
    }
    if(index < ui->baudrate_combo_box->count())
    {
        ui->baudrate_combo_box->setCurrentIndex(index);
    }
    else
    {
        ui->baudrate_combo_box->setCurrentIndex(0);
    }
}

void Device04_dialog::Parity_Init()
{
    QSettings save_Parity("Mysoft","MyApp");
    QVariant value = save_Parity.value("save_Parity",0);

    bool ok;
    int index = value.toInt(&ok);

    if(!ok)
    {
        QMessageBox::critical(this,"Loading Error","Error loading selection");
        return;
    }
    if(index < ui->parity_combo_box->count())
    {
        ui->parity_combo_box->setCurrentIndex(index);
    }
    else
    {
        ui->parity_combo_box->setCurrentIndex(0);
    }
}

void Device04_dialog::DataBits_Init()
{
    QSettings save_DataBits("Mysoft","MyApp");
    QVariant value = save_DataBits.value("save_DataBits",0);

    bool ok;
    int index = value.toInt(&ok);

    if(!ok)
    {
        QMessageBox::critical(this,"Loading Error","Error loading selection");
        return;
    }
    if(index < ui->data_bits_combo_box->count())
    {
        ui->data_bits_combo_box->setCurrentIndex(index);
    }
    else
    {
        ui->data_bits_combo_box->setCurrentIndex(0);
    }
}

void Device04_dialog::StopBit_Init()
{
    QSettings save_StopBit("Mysoft","MyApp");
    QVariant value = save_StopBit.value("save_StopBit",0);

    bool ok;
    int index = value.toInt(&ok);

    if(!ok)
    {
        QMessageBox::critical(this,"Loading Error","Error loading selection");
        return;
    }
    if(index < ui->stop_bits_combo_box->count())
    {
        ui->stop_bits_combo_box->setCurrentIndex(index);
    }
    else
    {
        ui->stop_bits_combo_box->setCurrentIndex(0);
    }
}

void Device04_dialog::Reg_init()
{
    QSettings save_Reg("Mysoft","MyApp");
    // restore value of QLineEdit
    QString text = save_Reg.value("save_Reg", "306").toString();
    ui->Reg_lineEdit->setText(text);
}

void Device04_dialog::Count_init()
{
    QSettings save_Count("Mysoft","MyApp");
    // restore value of QLineEdit
    QString text = save_Count.value("save_Count", "4").toString();
    ui->Count_lineEdit->setText(text);
}
