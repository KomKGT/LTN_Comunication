#include "start_dialog.h"
#include "ui_start_dialog.h"

Start_Dialog::Start_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Start_Dialog)
{
    ui->setupUi(this);


    status_button_state = "CANCEL";

}

Start_Dialog::~Start_Dialog()
{
    delete ui;
}

QString Start_Dialog::okBTN()
{
    return status_button_state;
}

Start_value Start_Dialog::getValue() const
{
    return value;
}

void Start_Dialog::setValue(const Start_value &value)
{
    this->value = value;
    ui->sec_spinbox->setValue(this->value.getTime().toInt());
    if(this->value.getChoose()==true)
    {
        ui->Automaically_Radio->setChecked(true);
        ui->Manually_Radio->setChecked(false);
    }
    else if(this->value.getChoose()==false)
    {
        ui->Automaically_Radio->setChecked(false);
        ui->Manually_Radio->setChecked(true);
    }
    else
    {
        ui->Automaically_Radio->setChecked(false);
        ui->Manually_Radio->setChecked(true);
    }

}

void Start_Dialog::on_buttonBox_accepted()
{
    if(ui->Manually_Radio->isChecked())
    {
        this->value.setChoose(false);
        this->value.setTime("999999");
        status_button_state = "OK";
        okBTN();
        accept();
    }
    else
    {
        this->value.setChoose(true);
        this->value.setTime(ui->sec_spinbox->text());
        status_button_state = "OK";
        okBTN();
        accept();
    }

}

void Start_Dialog::on_buttonBox_rejected()
{
    status_button_state = "CANCEL";
    okBTN();
    reject();
}
