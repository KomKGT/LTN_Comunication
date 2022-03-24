#include "device02_dialog.h"
#include "ui_device02_dialog.h"
#include <QSettings>
#include <QMessageBox>
//#include "device02_tcp.h"
Device02_dialog::Device02_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Device02_dialog)
{
    ui->setupUi(this);


    /*IPV4_init();    //Before fix
    Slave_init();   //Before fix
    Port_init();    //Before fix
    Reg_init();     //Before fix
    Count_init();   //Before fix */

    status_button_state = "CANCEL"; //Before fix
}

Device02_dialog::~Device02_dialog()     //Before fix
{
    delete ui;
}

QString Device02_dialog::IPV4_Selected()    //Before fix
{
    return  ui->IPv4_line_edit->text();
}

QString Device02_dialog::Slave_Selected()   //Before fix
{
    return ui->slave_line_edit->text();
}

QString Device02_dialog::Port_Selected()    //Before fix
{
    return ui->port_line_edit->text();
}

QString Device02_dialog::Reg_Selected() //Before fix
{
    return ui->rd_reg_line_edit->text();
}

QString Device02_dialog::Count_Selected()   //Before fix
{
    return ui->rd_count_line_edit->text();
}

QString Device02_dialog::OkBTN()    //Before fix
{
    return status_button_state;
}



void Device02_dialog::on_buttonBox_accepted()   //Before fix
{
    /*QSettings save_IPV4("Mysoft","MyApp");
    // save value from QLineEdit
    QString text_IPV4 = ui->IPv4_line_edit->text();
    save_IPV4.setValue("save_IPV4", text_IPV4);

    QSettings save_Slave("Mysoft","MyApp");
    // save value from QLineEdit
    QString text_Slave = ui->slave_line_edit->text();
    save_Slave.setValue("save_Slave", text_Slave);

    QSettings save_Port("Mysoft","MyApp");
    // save value from QLineEdit
    QString text_Port = ui->port_line_edit->text();
    save_Port.setValue("save_Port", text_Port);

    QSettings save_Reg("Mysoft","MyApp");
    // save value from QLineEdit
    QString text_Reg = ui->rd_reg_line_edit->text();
    save_Reg.setValue("save_Reg", text_Reg);

    QSettings save_Count("Mysoft","MyApp");
    // save value from QLineEdit
    QString text_Count = ui->rd_count_line_edit->text();
    save_Count.setValue("save_Count", text_Count);*/
    m_tcp.setIPv4(ui->IPv4_line_edit->text());
    m_tcp.setPort(ui->port_line_edit->text());
    m_tcp.setSlave(ui->slave_line_edit->text());
    m_tcp.setReg(ui->rd_reg_line_edit->text());
    m_tcp.setCount(ui->rd_count_line_edit->text());


    status_button_state = "OK";
    OkBTN();
    accept();
}

void Device02_dialog::on_buttonBox_rejected()   //Before fix
{
    status_button_state = "CANCEL";
    OkBTN();
    reject();
}

void Device02_dialog::IPV4_init()   //Before fix
{
    QSettings save_IPV4("Mysoft","MyApp");
    // restore value of QLineEdit
    QString text = save_IPV4.value("save_IPV4", "127.0.0.1").toString();
    ui->IPv4_line_edit->setText(text);
}

void Device02_dialog::Slave_init()  //Before fix
{
    QSettings save_Slave("Mysoft","MyApp");
    // restore value of QLineEdit
    QString text = save_Slave.value("save_Slave", "1").toString();
    ui->slave_line_edit->setText(text);
}

void Device02_dialog::Port_init()   //Before fix
{
    QSettings save_Port("Mysoft","MyApp");
    // restore value of QLineEdit
    QString text = save_Port.value("save_Port", "502").toString();
    ui->port_line_edit->setText(text);
}

void Device02_dialog::Reg_init()    //Before fix
{
    QSettings save_Reg("Mysoft","MyApp");
    // restore value of QLineEdit
    QString text = save_Reg.value("save_Reg", "306").toString();
    ui->rd_reg_line_edit->setText(text);
}

void Device02_dialog::Count_init()  //Before fix
{
    QSettings save_Count("Mysoft","MyApp");
    // restore value of QLineEdit
    QString text = save_Count.value("save_Count", "4").toString();
    ui->rd_count_line_edit->setText(text);
}

Property_TCP_DV2 Device02_dialog::tcp() const
{
    return m_tcp;
}

void Device02_dialog::setTcp(const Property_TCP_DV2 &tcp)
{
    m_tcp = tcp;

    ui->IPv4_line_edit->setText(m_tcp.getIPv4());
    ui->port_line_edit->setText(m_tcp.getPort());
    ui->slave_line_edit->setText(m_tcp.getSlave());
    ui->rd_reg_line_edit->setText(m_tcp.getReg());
    ui->rd_count_line_edit->setText(m_tcp.getCount());
}
