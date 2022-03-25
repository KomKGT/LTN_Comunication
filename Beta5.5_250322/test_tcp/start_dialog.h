#ifndef START_DIALOG_H
#define START_DIALOG_H

#include <QDialog>
#include "start_value.h"

namespace Ui {
class Start_Dialog;
}

class Start_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Start_Dialog(QWidget *parent = nullptr);
    ~Start_Dialog();
    QString okBTN();

    Start_value getValue() const;
    void setValue(const Start_value &value);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Start_Dialog *ui;
    Start_value value;

    QString status_button_state;

};

#endif // START_DIALOG_H
