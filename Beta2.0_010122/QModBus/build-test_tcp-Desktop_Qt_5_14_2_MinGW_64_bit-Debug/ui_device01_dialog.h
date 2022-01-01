/********************************************************************************
** Form generated from reading UI file 'device01_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICE01_DIALOG_H
#define UI_DEVICE01_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Device01_Dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *ComPort_Combobox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *BuadRate_ComboBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *DataBits_ComboBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *StopBit_ComboBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *Parity_ComboBox;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Device01_Dialog)
    {
        if (Device01_Dialog->objectName().isEmpty())
            Device01_Dialog->setObjectName(QString::fromUtf8("Device01_Dialog"));
        Device01_Dialog->resize(380, 244);
        verticalLayout_2 = new QVBoxLayout(Device01_Dialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(Device01_Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        ComPort_Combobox = new QComboBox(Device01_Dialog);
        ComPort_Combobox->setObjectName(QString::fromUtf8("ComPort_Combobox"));
        ComPort_Combobox->setFont(font);

        horizontalLayout->addWidget(ComPort_Combobox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(Device01_Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        BuadRate_ComboBox = new QComboBox(Device01_Dialog);
        BuadRate_ComboBox->setObjectName(QString::fromUtf8("BuadRate_ComboBox"));
        BuadRate_ComboBox->setFont(font);

        horizontalLayout_2->addWidget(BuadRate_ComboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(Device01_Dialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        horizontalLayout_3->addWidget(label_3);

        DataBits_ComboBox = new QComboBox(Device01_Dialog);
        DataBits_ComboBox->setObjectName(QString::fromUtf8("DataBits_ComboBox"));
        DataBits_ComboBox->setFont(font);

        horizontalLayout_3->addWidget(DataBits_ComboBox);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(Device01_Dialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        horizontalLayout_4->addWidget(label_4);

        StopBit_ComboBox = new QComboBox(Device01_Dialog);
        StopBit_ComboBox->setObjectName(QString::fromUtf8("StopBit_ComboBox"));
        StopBit_ComboBox->setFont(font);

        horizontalLayout_4->addWidget(StopBit_ComboBox);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(Device01_Dialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        horizontalLayout_5->addWidget(label_5);

        Parity_ComboBox = new QComboBox(Device01_Dialog);
        Parity_ComboBox->setObjectName(QString::fromUtf8("Parity_ComboBox"));
        Parity_ComboBox->setFont(font);

        horizontalLayout_5->addWidget(Parity_ComboBox);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(Device01_Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(Device01_Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Device01_Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Device01_Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Device01_Dialog);
    } // setupUi

    void retranslateUi(QDialog *Device01_Dialog)
    {
        Device01_Dialog->setWindowTitle(QCoreApplication::translate("Device01_Dialog", "Device 1 SerialPort", nullptr));
        label->setText(QCoreApplication::translate("Device01_Dialog", "COMPORT :", nullptr));
        label_2->setText(QCoreApplication::translate("Device01_Dialog", "BUADRATE :", nullptr));
        label_3->setText(QCoreApplication::translate("Device01_Dialog", "DATABIT :", nullptr));
        label_4->setText(QCoreApplication::translate("Device01_Dialog", "STOPBIT :", nullptr));
        label_5->setText(QCoreApplication::translate("Device01_Dialog", "PARITY :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Device01_Dialog: public Ui_Device01_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICE01_DIALOG_H
