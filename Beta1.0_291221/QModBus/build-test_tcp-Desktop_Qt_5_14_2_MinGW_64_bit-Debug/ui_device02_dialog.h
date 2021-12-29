/********************************************************************************
** Form generated from reading UI file 'device02_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICE02_DIALOG_H
#define UI_DEVICE02_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Device02_dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *IP_label;
    QLineEdit *IPv4_line_edit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *slave_line_edit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *port_label;
    QLineEdit *port_line_edit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *rd_reg_label;
    QLineEdit *rd_reg_line_edit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *rd_count_label;
    QLineEdit *rd_count_line_edit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Device02_dialog)
    {
        if (Device02_dialog->objectName().isEmpty())
            Device02_dialog->setObjectName(QString::fromUtf8("Device02_dialog"));
        Device02_dialog->resize(267, 238);
        verticalLayout_2 = new QVBoxLayout(Device02_dialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        IP_label = new QLabel(Device02_dialog);
        IP_label->setObjectName(QString::fromUtf8("IP_label"));
        QFont font;
        font.setPointSize(10);
        IP_label->setFont(font);

        horizontalLayout->addWidget(IP_label);

        IPv4_line_edit = new QLineEdit(Device02_dialog);
        IPv4_line_edit->setObjectName(QString::fromUtf8("IPv4_line_edit"));
        IPv4_line_edit->setMinimumSize(QSize(10, 0));
        IPv4_line_edit->setFont(font);
        IPv4_line_edit->setMaxLength(20);

        horizontalLayout->addWidget(IPv4_line_edit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(Device02_dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        slave_line_edit = new QLineEdit(Device02_dialog);
        slave_line_edit->setObjectName(QString::fromUtf8("slave_line_edit"));
        slave_line_edit->setMinimumSize(QSize(10, 0));
        slave_line_edit->setMaximumSize(QSize(16777215, 16777215));
        slave_line_edit->setFont(font);
        slave_line_edit->setMaxLength(10);

        horizontalLayout_2->addWidget(slave_line_edit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        port_label = new QLabel(Device02_dialog);
        port_label->setObjectName(QString::fromUtf8("port_label"));
        port_label->setFont(font);

        horizontalLayout_5->addWidget(port_label);

        port_line_edit = new QLineEdit(Device02_dialog);
        port_line_edit->setObjectName(QString::fromUtf8("port_line_edit"));
        port_line_edit->setFont(font);
        port_line_edit->setMaxLength(8);

        horizontalLayout_5->addWidget(port_line_edit);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        rd_reg_label = new QLabel(Device02_dialog);
        rd_reg_label->setObjectName(QString::fromUtf8("rd_reg_label"));
        rd_reg_label->setFont(font);

        horizontalLayout_3->addWidget(rd_reg_label);

        rd_reg_line_edit = new QLineEdit(Device02_dialog);
        rd_reg_line_edit->setObjectName(QString::fromUtf8("rd_reg_line_edit"));
        rd_reg_line_edit->setEnabled(true);
        rd_reg_line_edit->setFont(font);

        horizontalLayout_3->addWidget(rd_reg_line_edit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        rd_count_label = new QLabel(Device02_dialog);
        rd_count_label->setObjectName(QString::fromUtf8("rd_count_label"));
        rd_count_label->setFont(font);

        horizontalLayout_6->addWidget(rd_count_label);

        rd_count_line_edit = new QLineEdit(Device02_dialog);
        rd_count_line_edit->setObjectName(QString::fromUtf8("rd_count_line_edit"));
        rd_count_line_edit->setFont(font);

        horizontalLayout_6->addWidget(rd_count_line_edit);


        verticalLayout->addLayout(horizontalLayout_6);


        verticalLayout_2->addLayout(verticalLayout);

        buttonBox = new QDialogButtonBox(Device02_dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);

#if QT_CONFIG(shortcut)
        IP_label->setBuddy(IPv4_line_edit);
#endif // QT_CONFIG(shortcut)

        retranslateUi(Device02_dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Device02_dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Device02_dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Device02_dialog);
    } // setupUi

    void retranslateUi(QDialog *Device02_dialog)
    {
        Device02_dialog->setWindowTitle(QCoreApplication::translate("Device02_dialog", "Dialog", nullptr));
        IP_label->setText(QCoreApplication::translate("Device02_dialog", "IPv4:", nullptr));
#if QT_CONFIG(whatsthis)
        IPv4_line_edit->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        IPv4_line_edit->setText(QCoreApplication::translate("Device02_dialog", "192.168.1.1", nullptr));
        label->setText(QCoreApplication::translate("Device02_dialog", "Slave:", nullptr));
        slave_line_edit->setText(QCoreApplication::translate("Device02_dialog", "1", nullptr));
        port_label->setText(QCoreApplication::translate("Device02_dialog", "Port:", nullptr));
        port_line_edit->setText(QCoreApplication::translate("Device02_dialog", "502", nullptr));
        rd_reg_label->setText(QCoreApplication::translate("Device02_dialog", "Reg:", nullptr));
        rd_reg_line_edit->setText(QCoreApplication::translate("Device02_dialog", "306", nullptr));
        rd_count_label->setText(QCoreApplication::translate("Device02_dialog", "Count", nullptr));
        rd_count_line_edit->setText(QCoreApplication::translate("Device02_dialog", "4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Device02_dialog: public Ui_Device02_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICE02_DIALOG_H
