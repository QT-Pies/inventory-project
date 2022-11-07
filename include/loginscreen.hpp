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

#include <string>

#include "InventoryManager.hpp"


class LoginScreen : public QWidget{
    //Q_OBJECT
   public:
    LoginScreen(QWidget *parent = 0);
    ~LoginScreen();
    void openWindow(std::string);

   private slots:
    void loginApp();
    void quitApp();

   private:
    QWidget *w;
    QLineEdit *userLineEdit;
    QLineEdit *passwordLineEdit ;

    std::shared_ptr<InventoryManager> im;
};

#endif // LOGINSCREEN_HPP
