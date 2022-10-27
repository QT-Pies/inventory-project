#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
   public:
    /*
     * @brief takes in a username and password and account to create a new user
     * @param std::string for username
     * @param std::string for password
     */
    User(const std::string, const std::string, const std::string);

     /*
     * @brief takes in a username and password and account to create a new user
     * @param std::string for account_type
     * @return return true if able to update
     */
    bool updateAccount(const std::string);
   
   private:
    friend class Login;
    friend class InventoryManager;
    std::string name;
    std::string password;
    std::string account_type;
    int permission;
};

#endif