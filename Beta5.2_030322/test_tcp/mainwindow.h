#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "qmodbus.h"
#include "device01_dialog.h"
#include "device02_dialog.h"
#include "device03_dialog.h"
#include "device04_dialog.h"
#include "device02_tcp.h"
#include "property_tcp_dv2.h"
#include "property_rtu_dv4.h"
#include <QTimer>
#include <QVector>
#include <QTextStream>
#include <QPrinter>
#include <QCloseEvent>
#include <QMessageBox>
namespace Ui
{
    class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:

        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();


    public slots:
/*****************************************************************/
        //void connect_btn_clicked();                                 /*เดิม*/
        //void connect_to_dev();                                      /*เดิม*/
        //void disconnect_from_dev();                                 /*เดิม*/

        //void read_regs();                                           /*เดิม*/
        //void write_reg();                                           /*เดิม*/

        //void response_to_read_regs(int status);                     /*เดิม*/
        //void response_to_write_reg(int status);                     /*เดิม*/

        //void process_error(QModBus::ModBusError error);             /*เดิม*/
        //void change_status();                                       /*เดิม*/
/*****************************************************************/

/*****************************************************************/
        void device02_connect_to_dev();                             /*Device02 TCP*/
        void device02_disconnect_from_dev();                        /*Device02 TCP*/

        void device02_read_regs();                                  /*Device02 TCP*/
        //void write_reg();   /*เดิม*/

        void device02_response_to_read_regs(int status);            /*Device02 TCP*/
        //void response_to_write_reg(int status); /*เดิม*/

        void device02_process_error(QModBus::ModBusError error);    /*Device02 TCP*/
        void device02_change_status();                              /*Device02 TCP*/
/*****************************************************************/
        void device03_connect_to_dev();                             /*Device03 TCP UNUSE*/
        void device03_disconnect_from_dev();                        /*Device03 TCP UNUSE*/

        void device03_read_regs();                                  /*Device03 TCP UNUSE*/
        //void write_reg();   /*เดิม ซึ่งใช้แค่ Read*/

        void device03_response_to_read_regs(int status);            /*Device03 TCP UNUSE*/
        //void response_to_write_reg(int status); /*เดิม ซึ่งใช้แค่ Read*/

        void device03_process_error(QModBus::ModBusError error);    /*Device03 TCP UNUSE*/
        void device03_change_status();                              /*Device03 TCP UNUSE*/
/*****************************************************************/
        void device04_connect_to_dev();                             /*Device04 RTU*/
        void device04_disconnect_from_dev();                        /*Device04 RTU*/
        void device04_read_regs();                                  /*Device04 RTU*/
        void device04_response_to_read_regs(int status);            /*Device04 RTU*/
        void device04_process_error(QModBus::ModBusError error);    /*Device04 RTU*/
        void device04_change_status();                              /*Device04 RTU*/
/*************************ACTION SECTION************************************/

        void device01_dialog_exec();                                /*For Open Dialog01*/
        void device02_dialog_exec();                                /*For Open Dialog02*/
        void device03_dialog_exec();                                /*For Open Dialog03 UNUSE*/
        void device04_dialog_exec();                                /*For Open Dialog04*/
/*************************File SECTION************************************/
        void newFile();                             //New
        void openFile_dialog_exec();
        void Save(const QString &fileName);
        void saveAs();
        void chooseSave();
        void File_is_change();
        void File_is_change_init();
        void saveFile_MessageBox();
        void closeEvent(QCloseEvent *event);
        void printPreview();
        void renderPlot(QPrinter *printer);

        void device01_disconnect_from_dev();
        void device01_read();
        void device01_write();

private slots:
        void on_pushButton_clicked();

private:

        Ui::MainWindow *ui;                                         /*เดิม*/

        QModBus_TCP  mb;                                            /*เดิม*/

        uint16_t  rd_buf[MODBUS_MAX_READ_REGISTERS];                /*เดิม*/

        QSerialPort serial;                                         /*Device01 Normal Serialport*/

        QModBus_TCP  device02_mbTCP;                                /*Device02 TCP*/

        uint16_t  rd_buf_device02[MODBUS_MAX_READ_REGISTERS];       /*Device02 TCP*/

        QModBus_TCP device03_mbTCP;                                 /*Device03 TCP*/

        uint16_t  rd_buf_device03[MODBUS_MAX_READ_REGISTERS];       /*Device03 TCP*/

        QModBus_RTU device04_mbRTU;                                 /*Device04 TCP*/

        uint16_t  rd_buf_device04[MODBUS_MAX_READ_REGISTERS];       /*Device04 TCP*/


        Device01_Dialog *device01_dialog;
        Device02_dialog *device02_dialog;
        Device03_Dialog *device03_dialog;
        Device04_dialog *device04_dialog;

        QTimer *timer;  //device02
        QTimer *timer3; //device03
        QTimer *timer4; //device04

        QTimer *TestSerial;

        Property_TCP_DV2 m_tcp;

        Property_RTU_DV4 m_rtu;

        Property_SERIAL_DV1 m_serialport;

        void device01_connect_to_dev();


        /*OpenFile Dialog*/

        QVector<double> v_x;
        QVector<double> v_y;

        QVector<double> qv_x,qv_y;

        void setcurrentFile(const QString &fileName);
        QString currFile;

        bool save;                                  // check save

        QPixmap m_image;
         /*End OpenFile Dialog*/

        /*Encode Device1*/
        QString SplitCode(QStringList text,int*before,int*after);

};



#endif // MAINWINDOW_H
