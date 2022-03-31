#ifndef FEEDRATE_DIALOG_H
#define FEEDRATE_DIALOG_H

#include <QDialog>
#include "feedrate_value.h"

namespace Ui {
class FeedRate_Dialog;
}

class FeedRate_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit FeedRate_Dialog(QWidget *parent = nullptr);
    ~FeedRate_Dialog();

    QString OkBTN();

    FeedRate_value getScale() const;
    void setScale(const FeedRate_value &value);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::FeedRate_Dialog *ui;
    FeedRate_value scale;

    QString status_button_state;
};

#endif // FEEDRATE_DIALOG_H
