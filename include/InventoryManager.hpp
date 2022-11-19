#ifndef INVENTORY_MANAGER_HPP
#define INVENTORY_MANAGER_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <QApplication>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QToolButton>
#include <QString>
#include <QStringList>
#include <QWidget>

#include "ActiveInventory.hpp"
#include "Logger.hpp"
#include "Login.hpp"
#include "NonPerishableItem.hpp"
#include "PerishableItem.hpp"
#include "Sales.hpp"

class QInventoryManager : public QObject {
public:
    void itemChanged(QTableWidgetItem *);
};

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
     * @brief call updateUser in User class
     * @return return true if successful and false if not
     * @param std::string username
     * @param std::string account_type
     */
    bool updatePermission(std::string, std::string);

   private:
    bool command_line;
    std::shared_ptr<ActiveInventory> active_inventory{new ActiveInventory};
    std::shared_ptr<Login> login{new Login};
    std::shared_ptr<User> current_user;
    std::shared_ptr<SaleList> sale_list{new SaleList};
    std::string file_name;

    std::vector<std::shared_ptr<QObject>> view_gc;
    std::vector<QObject*> gc;
    std::shared_ptr<QApplication> app;
    std::shared_ptr<QWidget> window;
    std::shared_ptr<QWidget> view;
    std::shared_ptr<QTableWidget> table;
    QStringList inv_header;

    void initializeSidePanel();

    static void inventoryItemChanged(QTableWidgetItem*);
};

#endif
