#include "property_tcp_dv2.h"



QString Property_TCP_DV2::getIPv4() const
{
    return IPv4;
}

void Property_TCP_DV2::setIPv4(const QString &value)
{
    IPv4 = value;
}

QString Property_TCP_DV2::getSlave() const
{
    return Slave;
}

void Property_TCP_DV2::setSlave(const QString &value)
{
    Slave = value;
}

QString Property_TCP_DV2::getPort() const
{
    return Port;
}

void Property_TCP_DV2::setPort(const QString &value)
{
    Port = value;
}

QString Property_TCP_DV2::getReg() const
{
    return Reg;
}

void Property_TCP_DV2::setReg(const QString &value)
{
    Reg = value;
}

QString Property_TCP_DV2::getCount() const
{
    return Count;
}

void Property_TCP_DV2::setCount(const QString &value)
{
    Count = value;
}
