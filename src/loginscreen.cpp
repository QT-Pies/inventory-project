#include "loginscreen.hpp"

LoginScreen::LoginScreen(QWidget *parent) :
    QWidget(parent)
{
    w = new QWidget();
    //im = std::make_shared<InventoryManager>(false, file);
}

LoginScreen::~LoginScreen() {
    delete w;
    delete userLineEdit;
    delete passwordLineEdit;
}

// change everything to smart pointers
void LoginScreen::openWindow(std::string file) {
    im = std::make_shared<InventoryManager>(false, file);
    //w->
    w->setWindowTitle("Inventory Manager");

    QHBoxLayout *hUserLayout = new QHBoxLayout;
    QLabel *userLabel = new QLabel;
    userLineEdit = new QLineEdit;
    userLabel->setBuddy(userLineEdit);
    userLabel->setText("Username");
    hUserLayout->addWidget(userLabel);
    hUserLayout->addWidget(userLineEdit);

    QHBoxLayout *hPasswordLayout = new QHBoxLayout;
    QLabel *passwordLabel = new QLabel;
    passwordLineEdit = new QLineEdit;
    passwordLabel->setBuddy(passwordLineEdit);
    passwordLabel->setText("Password ");
    hPasswordLayout->addWidget(passwordLabel);
    hPasswordLayout->addWidget(passwordLineEdit);

    QHBoxLayout *hButtonsLayout = new QHBoxLayout;
    QPushButton *bLogin = new QPushButton("Login");
    QPushButton *bQuit = new QPushButton("Quit");
    hButtonsLayout->addWidget(bLogin);
    hButtonsLayout->addWidget(bQuit);

    // make this a pixle map
    QPixmap pix("IM_LOGO_RD.png");
    QLabel *imLabel = new QLabel;
    int wid = userLabel->width();
    imLabel->setPixmap(pix.scaled(wid/2,wid/2,Qt::KeepAspectRatio));

    QVBoxLayout *vLoginLayout = new QVBoxLayout;
    vLoginLayout->addWidget(imLabel);
    vLoginLayout->addLayout(hUserLayout);
    vLoginLayout->addLayout(hPasswordLayout);
    vLoginLayout->addLayout(hButtonsLayout);


    w->setLayout(vLoginLayout);

    //connect(bQuit, SIGNAL(clicked()), w, SLOT(quitApp()));
    connect(bLogin, &QPushButton::clicked, this, &LoginScreen::loginApp);
    connect(bQuit, &QPushButton::clicked, this, &LoginScreen::quitApp);

    w->show();
}

void LoginScreen::loginApp() {
    QString un = userLineEdit->text();
    QString pas = passwordLineEdit->text();

    if(im->guiLogin(un.toStdString(), pas.toStdString())) {
        QMessageBox::information(w, "Login", "Loggin Sucsessful");
        w->hide();
    }
    else {
        QMessageBox::warning(w,"Login", "Username and/or password is incorrect");
    }

}

void LoginScreen::quitApp() {
    w->close();
}