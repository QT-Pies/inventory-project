#ifndef LOGINSCREEN_HPP
#define LOGINSCREEN_HPP

#include <QDialog>

namespace Ui {
class LoginScreen;
}

class LoginScreen : public QDialog
{
    Q_OBJECT

public:
    explicit LoginScreen(QWidget *parent = nullptr);
    ~LoginScreen();

private:
    Ui::LoginScreen *ui;
};

#endif // LOGINSCREEN_HPP
