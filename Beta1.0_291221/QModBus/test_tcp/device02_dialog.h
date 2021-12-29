#ifndef DEVICE02_DIALOG_H
#define DEVICE02_DIALOG_H

#include <QDialog>

namespace Ui {
class Device02_dialog;
}

class Device02_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Device02_dialog(QWidget *parent = nullptr);
    ~Device02_dialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Device02_dialog *ui;

    void IPV4_init();
    void Slave_init();
    void Port_init();
    void Reg_init();
    void Count_init();
};

#endif // DEVICE02_DIALOG_H
