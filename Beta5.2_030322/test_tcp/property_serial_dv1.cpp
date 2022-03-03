#include "property_serial_dv1.h"



QString Property_SERIAL_DV1::getComPort() const
{
    return ComPort;
}

void Property_SERIAL_DV1::setComPort(const QString &value)
{
    ComPort = value;
}

QString Property_SERIAL_DV1::getBuadRate() const
{
    return BuadRate;
}

void Property_SERIAL_DV1::setBuadRate(const QString &value)
{
    BuadRate = value;
}

QString Property_SERIAL_DV1::getDataBits() const
{
    return DataBits;
}

void Property_SERIAL_DV1::setDataBits(const QString &value)
{
    DataBits = value;
}

QString Property_SERIAL_DV1::getStopBits() const
{
    return StopBits;
}

void Property_SERIAL_DV1::setStopBits(const QString &value)
{
    StopBits = value;
}

QString Property_SERIAL_DV1::getParity() const
{
    return Parity;
}

void Property_SERIAL_DV1::setParity(const QString &value)
{
    Parity = value;
}

QString Property_SERIAL_DV1::getFlowControl() const
{
    return FlowControl;
}

void Property_SERIAL_DV1::setFlowControl(const QString &value)
{
    FlowControl = value;
}
