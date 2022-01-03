#include "device01_dialog.h"
#include "ui_device01_dialog.h"


Device01_Dialog::Device01_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Device01_Dialog)
{
    ui->setupUi(this);
    AllComboBoxItemLoad();
    Load_Init();

}

Device01_Dialog::~Device01_Dialog()
{
    delete ui;
}

QString Device01_Dialog::ComPort_Selected()
{
    return ui->ComPort_Combobox->currentText();
}

QString Device01_Dialog::BuadRate_Selected()
{
    return  ui->BuadRate_ComboBox->currentText();
}

QString Device01_Dialog::DataBits_Selected()
{
    return ui->DataBits_ComboBox->currentText();
}

QString Device01_Dialog::StopBit_Selected()
{
    return ui->StopBit_ComboBox->currentText();
}

QString Device01_Dialog::Parity_Selected()
{
    return ui->Parity_ComboBox->currentText();
}


void Device01_Dialog::on_buttonBox_accepted()
{
    QSettings save_ComPort("Mysoft","MyApp");
    save_ComPort.setValue("save_ComPort",ui->ComPort_Combobox->currentIndex());

    QSettings save_BuadRate("Mysoft","MyApp");
    save_BuadRate.setValue("save_BuadRate",ui->BuadRate_ComboBox->currentIndex());

    QSettings save_DataBits("Mysoft","MyApp");
    save_DataBits.setValue("save_DataBits",ui->DataBits_ComboBox->currentIndex());

    QSettings save_StopBit("Mysoft","MyApp");
    save_StopBit.setValue("save_StopBit",ui->StopBit_ComboBox->currentIndex());

    QSettings save_Parity("Mysoft","MyApp");
    save_Parity.setValue("save_Parity",ui->Parity_ComboBox->currentIndex());

    accept();
}

void Device01_Dialog::on_buttonBox_rejected()
{
    reject();
}

void Device01_Dialog::AllComboBoxItemLoad()
{
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        ui->ComPort_Combobox->addItem(info.portName());
    }

    ui->BuadRate_ComboBox->addItems({"1200","2400","4800","9600","19200","38400","57600","115200"});

    ui->DataBits_ComboBox->addItems({"5","6","7","8"});

    ui->StopBit_ComboBox->addItems({"1","1.5","2"});

    ui->Parity_ComboBox->addItems({"NoParity","OddParity","EvenParity","MarkParity","SpaceParity"});
}

void Device01_Dialog::Load_Init()
{
    ComPort_Init();
    BuadRate_Init();
    DataBits_Init();
    StopBit_Init();
    Parity_Init();
}

void Device01_Dialog::ComPort_Init()
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

void Device01_Dialog::BuadRate_Init()
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
    if(index < ui->BuadRate_ComboBox->count())
    {
        ui->BuadRate_ComboBox->setCurrentIndex(index);
    }
    else
    {
        ui->BuadRate_ComboBox->setCurrentIndex(0);
    }
}

void Device01_Dialog::DataBits_Init()
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
    if(index < ui->DataBits_ComboBox->count())
    {
        ui->DataBits_ComboBox->setCurrentIndex(index);
    }
    else
    {
        ui->DataBits_ComboBox->setCurrentIndex(0);
    }
}

void Device01_Dialog::StopBit_Init()
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
    if(index < ui->StopBit_ComboBox->count())
    {
        ui->StopBit_ComboBox->setCurrentIndex(index);
    }
    else
    {
        ui->StopBit_ComboBox->setCurrentIndex(0);
    }
}

void Device01_Dialog::Parity_Init()
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
    if(index < ui->Parity_ComboBox->count())
    {
        ui->Parity_ComboBox->setCurrentIndex(index);
    }
    else
    {
        ui->Parity_ComboBox->setCurrentIndex(0);
    }
}
