#ifndef START_VALUE_H
#define START_VALUE_H
#include<QObject>
#include<QString>

class Start_value
{
public:

    QString getTime() const;
    void setTime(const QString &value);



    bool getChoose() const;
    void setChoose(bool value);

private:
    QString time;
    bool choose;
};

#endif // START_VALUE_H
