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
#include "feedrate_dialog.h"
#include "feedrate_value.h"
#include "start_dialog.h"
#include "start_value.h"
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

        void feedrate_dialog_exec();
        void start_dialog_exec();
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

        void UnitChangeBar_C();
        void UnitChangePSI_F();
        void UnitChangePSI_C();

        void UnitChangeFeedRate_RPM();

        void on_New_BTN_clicked();

        void on_OPEN_BTN_clicked();

        void on_SAVE_BTN_clicked();

        void on_PRINT_BTN_clicked();

        void on_SerialPort_BTN_clicked();

        void on_Reset_Data_BTN_clicked();

        void on_START_BTN_clicked();



        void tiktok(); //เอามาเทสเฉยๆไม่ได้ใช้จริง

        void on_END_BTN_clicked();

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

        FeedRate_Dialog *feedrate_dialog;
        Start_Dialog    *start_dialog;


        QTimer *timer;  //device02
        QTimer *timer3; //device03
        QTimer *timer4; //device04

        QTimer *TestSerial;

        Property_TCP_DV2 m_tcp;

        Property_RTU_DV4 m_rtu;

        Property_SERIAL_DV1 m_serialport;

        FeedRate_value scale;

        Start_value value;

        void device01_connect_to_dev();

        /*Store Graph*/
        int icount;
        //QVector<double> v_x1;
        double P2;
        QVector<double> v_y1;
        QVector<double> qv_x1,qv_y1;

        //QVector<double> v_x2;
        double T2;//Temp at screen
        QVector<double> v_y2;
        QVector<double> qv_x2,qv_y2;

        //QVector<double> v_x3;
        double T1; //Temp at pump inlet
        QVector<double> v_y3;
        QVector<double> qv_x3,qv_y3;

        //QVector<double> v_x4;
        double P1;//Pump inlet Pressure
        QVector<double> v_y4;
        QVector<double> qv_x4,qv_y4;

        //QVector<double> v_x5;
        double Gp;
        QVector<double> v_y5;
        QVector<double> qv_x5,qv_y5;

        //QVector<double> v_x6;
        QVector<double> v_y6;
        QVector<double> qv_x6,qv_y6;

        //QVector<double> v_x7;
        QVector<double> v_y7;
        QVector<double> qv_x7,qv_y7;

        //QVector<double> v_x8;
        QVector<double> v_y8;
        QVector<double> qv_x8,qv_y8;

        QVector<double> v_maxValue;
        QVector<double> v_minValue;

        QVector<double> time;//ไว้ตอน Open file

        /*End Store Graph*/

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

        void serialport_Constructor();
        void modbus_tcp_dv02_Constructor();
        void modbus_tcp_dv03_Constructor();
        void modbus_rtu_dv04_Constructor();

        void device_action_Constructor();
        void file_action_Constructor();

        void change_unit_action_Constructor();
        void graph_Constructor();

        void file_is_change_Constructor();
        void disconnect_button_Constructor();

        /*รันเวลา*/
        QTimer *RunTime;
        int sec; //เทสเฉยๆ ไม่ได้ใช้จริง
        /*รันเวลา*/

        /*Hide and Show Graph&Legend*/
        void Hide_And_Show_All_Graph();
        void Hide_And_Show_P1_Graph();
        void Hide_And_Show_P2_Graph();
        void Hide_And_Show_T1_Graph();
        void Hide_And_Show_T2_Graph();
        void Hide_And_Show_P1O_Graph();
        void Hide_And_Show_P2O_Graph();
        void Hide_And_Show_T1O_Graph();
        void Hide_And_Show_T2O_Graph();
        void Hide_And_Show_Ext_Graph();
        void Hide_And_Show_A1_Graph();
        void Hide_And_Show_Gp_Graph();
        void Hide_And_Show_A2_Graph();
        void Hide_And_Show_ExtO_Graph();
        void Hide_And_Show_A1O_Graph();
        void Hide_And_Show_GpO_Graph();
        void Hide_And_Show_A2O_Graph();
        /*Hide and Show Graph&Legend*/

};



#endif // MAINWINDOW_H
