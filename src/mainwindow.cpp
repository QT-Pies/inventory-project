#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "InventoryManager.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connect();
}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::on_pushButtonLOAD_clicked()
{
    ui->label->setText("LOADED FILE");
    return true;
}

