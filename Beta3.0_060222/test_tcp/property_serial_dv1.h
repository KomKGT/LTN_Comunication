#ifndef PROPERTY_SERIAL_DV1_H
#define PROPERTY_SERIAL_DV1_H
#include<QObject>
#include<QString>

class Property_SERIAL_DV1
{
public:


    QString getComPort() const;
    void setComPort(const QString &value);

    QString getBuadRate() const;
    void setBuadRate(const QString &value);

    QString getDataBits() const;
    void setDataBits(const QString &value);

    QString getStopBits() const;
    void setStopBits(const QString &value);

    QString getParity() const;
    void setParity(const QString &value);

private:
    QString ComPort;
    QString BuadRate;
    QString DataBits;
    QString StopBits;
    QString Parity;
};

#endif // PROPERTY_SERIAL_DV1_H
