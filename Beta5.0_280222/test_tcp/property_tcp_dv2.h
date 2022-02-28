#ifndef PROPERTY_TCP_DV2_H
#define PROPERTY_TCP_DV2_H
#include<QObject>
#include<QString>

class Property_TCP_DV2
{
public:


    QString getIPv4() const;
    void setIPv4(const QString &value);

    QString getSlave() const;
    void setSlave(const QString &value);

    QString getPort() const;
    void setPort(const QString &value);

    QString getReg() const;
    void setReg(const QString &value);

    QString getCount() const;
    void setCount(const QString &value);

private:
    QString IPv4;
    QString Slave;
    QString Port;
    QString Reg;
    QString Count;
};

#endif // PROPERTY_TCP_DV2_H
