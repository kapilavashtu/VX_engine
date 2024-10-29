#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H

#include <QWidget>

namespace Ui {
class ControlBlock;
}

class ControlBlock : public QWidget
{
    Q_OBJECT

public:
    explicit ControlBlock(QWidget *parent = nullptr);
    ~ControlBlock();

private:
    Ui::ControlBlock *ui;
};

#endif // CONTROLBLOCK_H
