#ifndef LOGICWORKER_H
#define LOGICWORKER_H

#include <QObject>

class LogicWorker : public QObject
{
    Q_OBJECT
public:
    explicit LogicWorker(QObject *parent = nullptr);

signals:

};

#endif // LOGICWORKER_H
