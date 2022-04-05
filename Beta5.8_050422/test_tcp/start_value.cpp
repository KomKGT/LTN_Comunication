#include "start_value.h"



QString Start_value::getTime() const
{
    return time;
}

void Start_value::setTime(const QString &value)
{
    time = value;
}

bool Start_value::getChoose() const
{
    return choose;
}

void Start_value::setChoose(bool value)
{
    choose = value;
}

