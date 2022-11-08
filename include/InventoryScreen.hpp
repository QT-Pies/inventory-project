#ifndef INVENTORYSCREEN_HPP
#define INVENTORYSCREEN_HPP

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPixmap>
#include <QListWidget>

#include <string>
#include "InventoryManager.hpp"



class InventoryScreen : public QWidget{
    //Q_OBJECT
   public:
   /*
    * @breif basic QT widget constructor
    */
    InventoryScreen(QWidget *parent = 0);

    /*
     * @breif deconstructor, since QT uses pointers it deletes them
     */
    ~InventoryScreen();

    /*
     * @breif Opens window that shows inventory 
     * @param Takes in ptr for inventory manager to pass between windows
     */
    void OpenWindow(std::shared_ptr<InventoryManager>);

   private slots:
    /*
     * @breif closes window on button press
     */
    void QuitApp();

   private:
    QWidget *w;
    std::shared_ptr<InventoryManager> im;
};

#endif