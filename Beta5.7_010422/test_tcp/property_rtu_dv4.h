#ifndef PROPERTY_RTU_DV4_H
#define PROPERTY_RTU_DV4_H
#include<QObject>
#include<QString>

class Property_RTU_DV4
{
public:


    QString getComPort() const;
    void setComPort(const QString &value);

    QString getSlave() const;
    void setSlave(const QString &value);

    QString getBuadRate() const;
    void setBuadRate(const QString &value);

    QString getParity() const;
    void setParity(const QString &value);

    QString getDataBits() const;
    void setDataBits(const QString &value);

    QString getStopBits() const;
    void setStopBits(const QString &value);

    QString getReg() const;
    void setReg(const QString &value);

    QString getCount() const;
    void setCount(const QString &value);

private:
    QString ComPort;
    QString Slave;
    QString BuadRate;
    QString Parity;
    QString DataBits;
    QString StopBits;
    QString Reg;
    QString Count;
    int k;
};

#endif // PROPERTY_RTU_DV4_H
