#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// #include "InventoryManager.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    friend class InventoryManager;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    bool on_pushButtonLOAD_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
