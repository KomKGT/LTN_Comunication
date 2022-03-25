#include "feedrate_dialog.h"
#include "ui_feedrate_dialog.h"

FeedRate_Dialog::FeedRate_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FeedRate_Dialog)
{
    ui->setupUi(this);

    status_button_state = "CANCEL";

}

FeedRate_Dialog::~FeedRate_Dialog()
{
    delete ui;
}

QString FeedRate_Dialog::OkBTN()
{
    return status_button_state;
}

void FeedRate_Dialog::on_buttonBox_accepted()
{
    scale.setCc_min_scale(ui->CCslashMin_LE->text());
    status_button_state = "OK";
    OkBTN();
    accept();
}

void FeedRate_Dialog::on_buttonBox_rejected()
{
    status_button_state = "CANCEL";
    OkBTN();
    reject();
}

FeedRate_value FeedRate_Dialog::getScale() const
{
    return scale;
}

void FeedRate_Dialog::setScale(const FeedRate_value &value)
{
    scale = value;

    ui->CCslashMin_LE->setText(scale.getCc_min_scale());
}


