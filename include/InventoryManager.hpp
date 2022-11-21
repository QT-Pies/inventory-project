#ifndef INVENTORY_MANAGER_HPP
#define INVENTORY_MANAGER_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <QApplication>
#include <QIcon>
#include <QInputDialog>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QToolButton>
#include <QToolBar>
#include <QString>
#include <QStringList>
#include <QWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QPixmap>
#include <QRadioButton>

#include "ActiveInventory.hpp"
#include "AddDialog.hpp"
#include "Logger.hpp"
#include "Login.hpp"
#include "NonPerishableItem.hpp"
#include "PerishableItem.hpp"
#include "Sales.hpp"
#include "SalesComparison.hpp"

class InventoryManager {
   public:
    /*
     * @brief Constructor; specifies whether CLI mode is enabled, and the file to
     * open.
     * @param bool CLI mode
     * @param std::string Inventory file to read in
     */
    InventoryManager(const bool, const std::string);

    /* @brief Destructor; does nothing */
    ~InventoryManager();

    /*
     * @brief Reads standard input from user
     * @return 0 on success, -1 on failure
     */
    int userInput();

    /*
     * @brief temp function to display inventory.
    */
    int displayInventory();

    void helpScreen();

    /*
     * @brief Starts up a Qt application of the IM.
     * @return 0 on success, -1 on failure.
    */
    int guiInput(int, char**);

    /*
     * @brief Reads in CSV file and stores it into active_inventory
     */
    void readCSVFile();

    /*
     * @brief Saves the current inventory to disk
     * @return 0 on success, -1 on failure
     */
    int fileOutput();

    /*
     * @brief call userInput in Login class
     * @return return true if successful login and false if not
     */
    bool userLogin();

    /*
     * @brief Main GUI view
     */
    void mainWindow();

    /*
     * @brief GUI login
     */
    void guiLogin();

    /*
     * @breif User view, includes adding user, changing premmisions, and log out
     */
    void guiUser();

     /*
     * @breif Sale Comparison view
     */
    void guiSaleComparison();

    /*
     * @brief call updateUser in User class
     * @return return true if successful and false if not
     * @param std::string username
     * @param std::string account_type
     */
    bool updatePermission(std::string, std::string);

    /*
     * @brief calls process transaction function in Transaction
     */
    void makeTransaction();

   private:
    bool command_line;
    std::shared_ptr<ActiveInventory> active_inventory{new ActiveInventory};
    std::shared_ptr<Login> login{new Login};
    std::shared_ptr<User> current_user;
    std::shared_ptr<SaleList> sale_list{new SaleList};
    std::shared_ptr<SalesComparison> sales_comp{new SalesComparison};
    std::string file_name;

    std::vector<std::shared_ptr<QObject>> view_gc;
    std::vector<QObject*> gc;
    
    /* Class wide QObject variables */
    std::shared_ptr<QApplication> app; // The QApplication context.
    std::shared_ptr<QWidget> window; // The "main window" widget.
    std::shared_ptr<QWidget> view; // The "view" -- login, main program view.
    std::shared_ptr<QWidget> sub_view; // The "sub-view" -- inventory, users, help, etc.
    QStringList inv_header;
    QStringList item_fields;
    /* used for login and in user screen */
    QLineEdit *username_line;
    QLineEdit *password_line;
    /* used in user screen */
    QRadioButton *ownerButton;
    QRadioButton *managerButton;
    QRadioButton *employeeButton;
    /* used in Sales Comparison */
    QLineEdit *years_line;

    /* Specific QWidget objects */
    std::shared_ptr<QTableWidget> table;

    std::shared_ptr<QWidget> inv_screen;
    std::shared_ptr<QWidget> user_screen;
    std::shared_ptr<QWidget> help_screen;
    std::shared_ptr<QWidget> sc_screen;

    /*
     * @brief Displays side panel.
     */
    void initializeSidePanel();

    void insertItemIntoTable(std::shared_ptr<Item>, int);

    void redrawTable();

    void hideAllViews();

    /* Other variables for Qt */
    bool inv_update_debounce;
};

#endif
