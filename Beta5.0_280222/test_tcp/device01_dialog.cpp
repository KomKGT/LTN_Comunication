#include "device01_dialog.h"
#include "ui_device01_dialog.h"


Device01_Dialog::Device01_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Device01_Dialog)
{
    ui->setupUi(this);
    AllComboBoxItemLoad();
    //Load_Init();

    status_button_state = "CANCEL";
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

QString Device01_Dialog::OkBTN()
{
    return status_button_state;
}


void Device01_Dialog::on_buttonBox_accepted()
{
    /*QSettings save_ComPort("Mysoft","MyApp");
    save_ComPort.setValue("save_ComPort",ui->ComPort_Combobox->currentIndex());

    QSettings save_BuadRate("Mysoft","MyApp");
    save_BuadRate.setValue("save_BuadRate",ui->BuadRate_ComboBox->currentIndex());

    QSettings save_DataBits("Mysoft","MyApp");
    save_DataBits.setValue("save_DataBits",ui->DataBits_ComboBox->currentIndex());

    QSettings save_StopBit("Mysoft","MyApp");
    save_StopBit.setValue("save_StopBit",ui->StopBit_ComboBox->currentIndex());

    QSettings save_Parity("Mysoft","MyApp");
    save_Parity.setValue("save_Parity",ui->Parity_ComboBox->currentIndex());*/

    m_serialport.setComPort(ui->ComPort_Combobox->currentText());
    m_serialport.setBuadRate(ui->BuadRate_ComboBox->currentText());
    m_serialport.setParity(ui->Parity_ComboBox->currentText());
    m_serialport.setDataBits(ui->DataBits_ComboBox->currentText());
    m_serialport.setStopBits(ui->StopBit_ComboBox->currentText());
    m_serialport.setFlowControl(ui->FlowControl_ComboBox->currentText());

    status_button_state = "OK";
    OkBTN();
    accept();
}

void Device01_Dialog::on_buttonBox_rejected()
{
    status_button_state = "CANCEL";
    OkBTN();
    reject();
}

void Device01_Dialog::AllComboBoxItemLoad()
{
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        ui->ComPort_Combobox->addItem(info.portName());
    }

    //ui->BuadRate_ComboBox->addItems({"1200","2400","4800","9600","19200","38400","57600","115200"});
    ui->BuadRate_ComboBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->BuadRate_ComboBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->BuadRate_ComboBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->BuadRate_ComboBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);


    //ui->DataBits_ComboBox->addItems({"5","6","7","8"});
    ui->DataBits_ComboBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->DataBits_ComboBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->DataBits_ComboBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->DataBits_ComboBox->addItem(QStringLiteral("8"), QSerialPort::Data8);

    //ui->StopBit_ComboBox->addItems({"1","1.5","2"});
    ui->StopBit_ComboBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
    ui->StopBit_ComboBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
    ui->StopBit_ComboBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);


    //ui->Parity_ComboBox->addItems({"NoParity","OddParity","EvenParity","MarkParity","SpaceParity"});
    ui->Parity_ComboBox->addItem(tr("None"), QSerialPort::NoParity);
    ui->Parity_ComboBox->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->Parity_ComboBox->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->Parity_ComboBox->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->Parity_ComboBox->addItem(tr("Space"), QSerialPort::SpaceParity);

    ui->FlowControl_ComboBox->addItem(tr("None"), QSerialPort::NoFlowControl);
    ui->FlowControl_ComboBox->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    ui->FlowControl_ComboBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
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

Property_SERIAL_DV1 Device01_Dialog::serialport() const
{
    return m_serialport;
}

void Device01_Dialog::setSerialport(const Property_SERIAL_DV1 &serialport)
{
    m_serialport = serialport;

    ui->ComPort_Combobox->setCurrentText(m_serialport.getComPort());
    ui->BuadRate_ComboBox->setCurrentText(m_serialport.getBuadRate());
    ui->Parity_ComboBox->setCurrentText(m_serialport.getParity());
    ui->DataBits_ComboBox->setCurrentText(m_serialport.getDataBits());
    ui->StopBit_ComboBox->setCurrentText(m_serialport.getStopBits());
    ui->FlowControl_ComboBox->setCurrentText(m_serialport.getFlowControl());
}
