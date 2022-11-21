#ifndef VIRTUALDBDRIVER_H
#define VIRTUALDBDRIVER_H

#include <QObject>

class VirtualDBDriver : public QObject
{
    Q_OBJECT
public:
    explicit VirtualDBDriver(QObject *parent = nullptr);

signals:

};

#endif // VIRTUALDBDRIVER_H
