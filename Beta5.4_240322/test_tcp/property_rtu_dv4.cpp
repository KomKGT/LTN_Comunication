#include "property_rtu_dv4.h"


QString Property_RTU_DV4::getComPort() const
{
    return ComPort;
}

void Property_RTU_DV4::setComPort(const QString &value)
{
    ComPort = value;
}

QString Property_RTU_DV4::getSlave() const
{
    return Slave;
}

void Property_RTU_DV4::setSlave(const QString &value)
{
    Slave = value;
}

QString Property_RTU_DV4::getBuadRate() const
{
    return BuadRate;
}

void Property_RTU_DV4::setBuadRate(const QString &value)
{
    BuadRate = value;
}

QString Property_RTU_DV4::getParity() const
{
    return Parity;
}

void Property_RTU_DV4::setParity(const QString &value)
{
    Parity = value;
}

QString Property_RTU_DV4::getDataBits() const
{
    return DataBits;
}

void Property_RTU_DV4::setDataBits(const QString &value)
{
    DataBits = value;
}

QString Property_RTU_DV4::getStopBits() const
{
    return StopBits;
}

void Property_RTU_DV4::setStopBits(const QString &value)
{
    StopBits = value;
}

QString Property_RTU_DV4::getReg() const
{
    return Reg;
}

void Property_RTU_DV4::setReg(const QString &value)
{
    Reg = value;
}

QString Property_RTU_DV4::getCount() const
{
    return Count;
}

void Property_RTU_DV4::setCount(const QString &value)
{
    Count = value;
}
