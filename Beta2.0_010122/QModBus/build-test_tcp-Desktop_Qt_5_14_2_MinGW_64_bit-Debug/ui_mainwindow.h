/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionDevice1;
    QAction *actionMODBUS_TCP;
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *IP_label;
    QLineEdit *IPv4_line_edit;
    QLabel *slave_label;
    QLineEdit *slave_line_edit;
    QLabel *port_label;
    QLineEdit *port_line_edit;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *rd_reg_label;
    QLineEdit *rd_reg_line_edit;
    QLabel *rd_count_label;
    QLineEdit *rd_count_line_edit;
    QPushButton *rd_button;
    QHBoxLayout *horizontalLayout_4;
    QLabel *wr_reg_label;
    QLineEdit *wr_reg_line_edit;
    QLabel *wr_val_label;
    QLineEdit *wr_val_line_edit;
    QPushButton *wr_button;
    QSpacerItem *horizontalSpacer;
    QPushButton *connect_button;
    QPlainTextEdit *log_plain_text_edit;
    QTextEdit *textEdit;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menus;
    QMenu *menuCommunication;
    QMenu *menuDevice_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(689, 495);
        MainWindow->setMaximumSize(QSize(700, 1000));
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        actionDevice1 = new QAction(MainWindow);
        actionDevice1->setObjectName(QString::fromUtf8("actionDevice1"));
        actionMODBUS_TCP = new QAction(MainWindow);
        actionMODBUS_TCP->setObjectName(QString::fromUtf8("actionMODBUS_TCP"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 50, 669, 100));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        IP_label = new QLabel(layoutWidget);
        IP_label->setObjectName(QString::fromUtf8("IP_label"));

        horizontalLayout->addWidget(IP_label);

        IPv4_line_edit = new QLineEdit(layoutWidget);
        IPv4_line_edit->setObjectName(QString::fromUtf8("IPv4_line_edit"));
        IPv4_line_edit->setMinimumSize(QSize(300, 0));
        IPv4_line_edit->setMaxLength(20);

        horizontalLayout->addWidget(IPv4_line_edit);

        slave_label = new QLabel(layoutWidget);
        slave_label->setObjectName(QString::fromUtf8("slave_label"));

        horizontalLayout->addWidget(slave_label);

        slave_line_edit = new QLineEdit(layoutWidget);
        slave_line_edit->setObjectName(QString::fromUtf8("slave_line_edit"));
        slave_line_edit->setMaximumSize(QSize(50, 16777215));
        slave_line_edit->setMaxLength(10);

        horizontalLayout->addWidget(slave_line_edit);

        port_label = new QLabel(layoutWidget);
        port_label->setObjectName(QString::fromUtf8("port_label"));

        horizontalLayout->addWidget(port_label);

        port_line_edit = new QLineEdit(layoutWidget);
        port_line_edit->setObjectName(QString::fromUtf8("port_line_edit"));
        port_line_edit->setMaxLength(8);

        horizontalLayout->addWidget(port_line_edit);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        rd_reg_label = new QLabel(layoutWidget);
        rd_reg_label->setObjectName(QString::fromUtf8("rd_reg_label"));

        horizontalLayout_3->addWidget(rd_reg_label);

        rd_reg_line_edit = new QLineEdit(layoutWidget);
        rd_reg_line_edit->setObjectName(QString::fromUtf8("rd_reg_line_edit"));
        rd_reg_line_edit->setEnabled(true);

        horizontalLayout_3->addWidget(rd_reg_line_edit);

        rd_count_label = new QLabel(layoutWidget);
        rd_count_label->setObjectName(QString::fromUtf8("rd_count_label"));

        horizontalLayout_3->addWidget(rd_count_label);

        rd_count_line_edit = new QLineEdit(layoutWidget);
        rd_count_line_edit->setObjectName(QString::fromUtf8("rd_count_line_edit"));

        horizontalLayout_3->addWidget(rd_count_line_edit);

        rd_button = new QPushButton(layoutWidget);
        rd_button->setObjectName(QString::fromUtf8("rd_button"));

        horizontalLayout_3->addWidget(rd_button);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        wr_reg_label = new QLabel(layoutWidget);
        wr_reg_label->setObjectName(QString::fromUtf8("wr_reg_label"));

        horizontalLayout_4->addWidget(wr_reg_label);

        wr_reg_line_edit = new QLineEdit(layoutWidget);
        wr_reg_line_edit->setObjectName(QString::fromUtf8("wr_reg_line_edit"));

        horizontalLayout_4->addWidget(wr_reg_line_edit);

        wr_val_label = new QLabel(layoutWidget);
        wr_val_label->setObjectName(QString::fromUtf8("wr_val_label"));

        horizontalLayout_4->addWidget(wr_val_label);

        wr_val_line_edit = new QLineEdit(layoutWidget);
        wr_val_line_edit->setObjectName(QString::fromUtf8("wr_val_line_edit"));

        horizontalLayout_4->addWidget(wr_val_line_edit);

        wr_button = new QPushButton(layoutWidget);
        wr_button->setObjectName(QString::fromUtf8("wr_button"));

        horizontalLayout_4->addWidget(wr_button);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_3->addLayout(verticalLayout_2);


        horizontalLayout_5->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        connect_button = new QPushButton(layoutWidget);
        connect_button->setObjectName(QString::fromUtf8("connect_button"));

        horizontalLayout_5->addWidget(connect_button);

        log_plain_text_edit = new QPlainTextEdit(centralWidget);
        log_plain_text_edit->setObjectName(QString::fromUtf8("log_plain_text_edit"));
        log_plain_text_edit->setGeometry(QRect(30, 190, 256, 250));
        log_plain_text_edit->setMinimumSize(QSize(0, 250));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(380, 190, 221, 161));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 689, 25));
        menus = new QMenu(menuBar);
        menus->setObjectName(QString::fromUtf8("menus"));
        menuCommunication = new QMenu(menus);
        menuCommunication->setObjectName(QString::fromUtf8("menuCommunication"));
        menuDevice_2 = new QMenu(menuCommunication);
        menuDevice_2->setObjectName(QString::fromUtf8("menuDevice_2"));
        MainWindow->setMenuBar(menuBar);
#if QT_CONFIG(shortcut)
        IP_label->setBuddy(IPv4_line_edit);
#endif // QT_CONFIG(shortcut)

        menuBar->addAction(menus->menuAction());
        menus->addAction(menuCommunication->menuAction());
        menuCommunication->addAction(actionDevice1);
        menuCommunication->addAction(menuDevice_2->menuAction());
        menuDevice_2->addAction(actionMODBUS_TCP);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Test_TCP", nullptr));
        actionDevice1->setText(QCoreApplication::translate("MainWindow", "Device 1", nullptr));
        actionMODBUS_TCP->setText(QCoreApplication::translate("MainWindow", "MODBUS TCP", nullptr));
        IP_label->setText(QCoreApplication::translate("MainWindow", "IPv4:", nullptr));
#if QT_CONFIG(whatsthis)
        IPv4_line_edit->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        IPv4_line_edit->setText(QCoreApplication::translate("MainWindow", "192.168.1.1", nullptr));
        slave_label->setText(QCoreApplication::translate("MainWindow", "Slave:", nullptr));
        slave_line_edit->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        port_label->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        port_line_edit->setText(QCoreApplication::translate("MainWindow", "502", nullptr));
        rd_reg_label->setText(QCoreApplication::translate("MainWindow", "Reg:", nullptr));
        rd_reg_line_edit->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        rd_count_label->setText(QCoreApplication::translate("MainWindow", "Count", nullptr));
        rd_count_line_edit->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        rd_button->setText(QCoreApplication::translate("MainWindow", "Read", nullptr));
        wr_reg_label->setText(QCoreApplication::translate("MainWindow", "Reg:", nullptr));
        wr_reg_line_edit->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        wr_val_label->setText(QCoreApplication::translate("MainWindow", "Value", nullptr));
        wr_val_line_edit->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        wr_button->setText(QCoreApplication::translate("MainWindow", "Write", nullptr));
        connect_button->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        menus->setTitle(QCoreApplication::translate("MainWindow", "Option", nullptr));
        menuCommunication->setTitle(QCoreApplication::translate("MainWindow", "Communication", nullptr));
        menuDevice_2->setTitle(QCoreApplication::translate("MainWindow", "Device 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
