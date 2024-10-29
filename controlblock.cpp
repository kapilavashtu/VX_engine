#include "controlblock.h"
#include "ui_controlblock.h"

ControlBlock::ControlBlock(QWidget *parent) : QWidget(parent), ui(new Ui::ControlBlock)
{
    ui->setupUi(this);
}

ControlBlock::~ControlBlock()
{
    delete ui;
}
