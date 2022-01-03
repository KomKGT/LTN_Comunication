#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "qmodbus.h"
#include "device01_dialog.h"
#include "device02_dialog.h"
#include "device02_tcp.h"
#include <QTimer>
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

        void connect_btn_clicked(); /*เดิม*/
        void connect_to_dev();      /*เดิม*/
        void disconnect_from_dev(); /*เดิม*/

        void read_regs();   /*เดิม*/
        void write_reg();   /*เดิม*/

        void response_to_read_regs(int status); /*เดิม*/
        void response_to_write_reg(int status); /*เดิม*/

        void process_error(QModBus::ModBusError error); /*เดิม*/
        void change_status();   /*เดิม*/
/*****************************************************************/
        void device02_connect_to_dev();
        void device02_disconnect_from_dev(); /*เดิม*/

        void device02_read_regs();   /*เดิม*/
        //void write_reg();   /*เดิม*/

        void device02_response_to_read_regs(int status); /*เดิม*/
        //void response_to_write_reg(int status); /*เดิม*/

        void device02_process_error(QModBus::ModBusError error); /*เดิม*/
        void device02_change_status();   /*เดิม*/
/*****************************************************************/
        void device01_dialog_exec();
        void device02_dialog_exec();

        void readData();

    private:

        Ui::MainWindow *ui; /*เดิม*/

        QModBus_TCP  mb;    /*เดิม*/

        uint16_t  rd_buf[MODBUS_MAX_READ_REGISTERS];    /*เดิม*/

        QModBus_TCP  device02_mbTCP;

        uint16_t  rd_buf_device02[MODBUS_MAX_READ_REGISTERS];

        Device01_Dialog *device01_dialog;
        Device02_dialog *device02_dialog;

        QTimer *timer;

        void ComPort_Set();
        void BuadRate_Set();
        void DataBits_Set();
        void StopBit_Set();
        void Parity_Set();

        void Device01_Property_Set();
};



#endif // MAINWINDOW_H
