#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <fstream>
#include <string>
#include <map>
#include <memory>

class User {
    public:
        /*
        * @brief takes in a username and password and account to create a new user
        * @param std::string for username
        * @param std::string for password
        * @param std::string account_type
        */
        User(std::string, std::string, std::string);
    private:
        std::string name;
        std::string password;
        std::string account_type;
        int permission;
};

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
        bool createUser(std::string, std::string, std::string);

        /*
         * @brief user will be able to login or create a new user
         * @return shared_ptr<User> 
        */
        std::shared_ptr<User> userInput();
        
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
        

    private:

       
        /*
         * stores file_name and valid users
        */
        std::string file_name;
        std::map <std::string, std::shared_ptr<User>> users;
        
};

#endif