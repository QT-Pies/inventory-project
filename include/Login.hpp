#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <string>
#include <map>
#include <memory>

class User {
    std::string name;
    std::string password;
    bool add;
    bool remove;
    bool update;
    bool print;
};

class Login {
    public:
        /*
         * @brief constructor will read in the filename
         * @param strd::string file_name
        */
        Login(std::string);
        

        ~Login();

        /*
         * @brief takes in a username and password to create a new user
         * @param std::string for username
         * @param std::string for password
         * @return returns true if user created and fasle if not 
        */
        bool createUser(std::string, std::string);

        /*
         * @brief user will be able to login or create a new user
         * @return shared_ptr<User> 
        */
        std::shared_ptr<User> userInput();

    private:

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
         * stores file_name and valid users
        */
        std::string file_name;
        std::map <std::string, std::shared_ptr<User> > users;
        
};

#endif