#ifndef MODBUSDRIVER_H
#define MODBUSDRIVER_H

#include <QObject>

class ModbusDriver : public QObject
{
    Q_OBJECT
public:
    explicit ModbusDriver(QObject *parent = nullptr);

signals:

};

#endif // MODBUSDRIVER_H
