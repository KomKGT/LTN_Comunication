#include "feedrate_value.h"

QString FeedRate_value::getCc_min_scale() const
{
    return cc_min_scale;
}

void FeedRate_value::setCc_min_scale(QString value)
{
    cc_min_scale = value;
}
