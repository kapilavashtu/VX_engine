#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //objects inits

    //set widgets params

    //set object & attributes params

    //set configs

    //set connections

    connect(ui->bigButton, &QPushButton::clicked, ui->bigButton, &QPushButton::hide);
    connect(ui->startButton, &QPushButton::clicked, ui->bigButton, &QPushButton::show);
    connect(ui->optionsButton, &QPushButton::clicked, this, &MainWindow::setText);
    //connect(ui->bigButton, &QPushButton::clicked, ui->bigButton, &QPushButton::hide);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setText()
{
    ui->textBrowser->setText("fffffffffffffffuck");
}

