#ifndef LOGINSCREEN_HPP
#define LOGINSCREEN_HPP

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
#include "InventoryScreen.hpp"


class LoginScreen : public QWidget{
    //Q_OBJECT
   public:
   /*
    * @breif basic QT widget constructor
    */
    LoginScreen(QWidget *parent = 0);

    /*
     * @breif deconstructor, since QT uses normal ptrs it deletes them
     */
    ~LoginScreen();

    /*
     * @breif opens window for login screen
     * @param std::string this is used for inventory manager constructor
     */
    void openWindow(std::string);

   private slots:
    /*
     * @breif Button user presses to try to login
     */
    void loginApp();

    /*
     * @breif Button user presses to close window
     */
    void quitApp();

   private:
    QWidget *w;
    QLineEdit *userLineEdit;
    QLineEdit *passwordLineEdit ;

    std::shared_ptr<InventoryManager> im;
    InventoryScreen *inventoryWindow;
};

#endif // LOGINSCREEN_HPP
