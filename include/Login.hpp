#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "HelperFunctions.hpp"
#include "Logger.hpp"
#include "User.hpp"

class Login {
   public:
    /*
     * @brief default constructor
     */
    Login();

    ~Login();

    /*
     * @brief takes in a username and password and account_type to create a new user
     * @param std::string for username
     * @param std::string for password
     * @param std::string account_type
     * @return returns true if user created and fasle if not
     */
    bool createUser(const std::string, const std::string, std::string);

    /*
     * @brief user will be able to login or create a new user
     * @return shared_ptr<User>
     */
    std::shared_ptr<User> userInput();

    std::shared_ptr<User> guiInput(std::string, std::string);

    /*
     * @brief reads in the user file
     * @return true if file read successfully
     * @return false if unable to read file
     */
    bool readCSV();

    /*
     * @brief outputs users map to file
     * @return true if successfull
     * @return false is unable to write to file
     */
    bool outputCSV();

    /*
     * @brief verifies username and password
     * @param std::string name
     * @param std::string password
     * @return shared_ptr to user
     */
    std::shared_ptr<User> verifyUser(const std::string, const std::string);

   private:
    std::string file_name = "accounts.csv";
    std::map<std::string, std::shared_ptr<User>> users;
};

#endif