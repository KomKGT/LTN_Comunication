#include "device02_dialog.h"
#include "ui_device02_dialog.h"
#include <QSettings>
#include <QMessageBox>

Device02_dialog::Device02_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Device02_dialog)
{
    ui->setupUi(this);
    IPV4_init();
    Slave_init();
    Port_init();
    Reg_init();
    Count_init();
}

Device02_dialog::~Device02_dialog()
{
    delete ui;
}

void Device02_dialog::on_buttonBox_accepted()
{
    QSettings save_IPV4("Mysoft","MyApp");
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
    save_Reg.setValue("save_Reg", text_Port);

    QSettings save_Count("Mysoft","MyApp");
    // save value from QLineEdit
    QString text_Count = ui->rd_count_line_edit->text();
    save_Count.setValue("save_Count", text_Count);

    accept();
}

void Device02_dialog::on_buttonBox_rejected()
{
    reject();
}

void Device02_dialog::IPV4_init()
{
    QSettings save_IPV4("Mysoft","MyApp");
    // restore value of QLineEdit
    QString text = save_IPV4.value("save_IPV4", "127.0.0.1").toString();
    ui->IPv4_line_edit->setText(text);
}

void Device02_dialog::Slave_init()
{
    QSettings save_Slave("Mysoft","MyApp");
    // restore value of QLineEdit
    QString text = save_Slave.value("save_Slave", "1").toString();
    ui->slave_line_edit->setText(text);
}

void Device02_dialog::Port_init()
{
    QSettings save_Port("Mysoft","MyApp");
    // restore value of QLineEdit
    QString text = save_Port.value("save_Port", "502").toString();
    ui->port_line_edit->setText(text);
}

void Device02_dialog::Reg_init()
{
    QSettings save_Reg("Mysoft","MyApp");
    // restore value of QLineEdit
    QString text = save_Reg.value("save_Reg", "306").toString();
    ui->rd_reg_line_edit->setText(text);
}

void Device02_dialog::Count_init()
{
    QSettings save_Count("Mysoft","MyApp");
    // restore value of QLineEdit
    QString text = save_Count.value("save_Count", "4").toString();
    ui->rd_count_line_edit->setText(text);
}
