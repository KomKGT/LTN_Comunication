#ifndef FEEDRATE_VALUE_H
#define FEEDRATE_VALUE_H

#include <QObject>
#include <QString>

class FeedRate_value
{
public:

    QString getCc_min_scale() const;
    void setCc_min_scale(QString value);

private:
    QString cc_min_scale;
};

#endif // FEEDRATE_VALUE_H
