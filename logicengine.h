#ifndef LOGICENGINE_H
#define LOGICENGINE_H

#include <QObject>

class LogicEngine : public QObject
{
    Q_OBJECT
public:
    explicit LogicEngine(QObject *parent = nullptr);

signals:

};

#endif // LOGICENGINE_H
