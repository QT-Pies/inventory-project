#include "Login.hpp"

User::User(std::string username, std::string pswd, std::string acc_type) {

    name = username;
    password = pswd;
    account_type = acc_type;

    if(acc_type == "owner") permission = 5;
    if(acc_type == "manager") permission = 3;
    if(acc_type == "employee") permission = 1;
}

Login::Login() {
    /* does nothing */
}

Login::~Login() {
    /* no deletion required*/
}

bool Login::createUser(std::string name, std::string password, std::string account) {

    if(users.find(name) != users.end()) {
        std::shared_ptr<User> new_user = std::make_shared<User>(name, password, account);
    } else {
        fprintf(stderr, "User %s already exists\n", name.c_str());
        return false;
    }

    return true;
}

  
bool Login::readCSV() {

    std::string head, name, password, account;
    bool created;
    std::ifstream user_file(file_name);
    
    if(!user_file.is_open()) {
        fprintf(stderr, "Unable to open %s\n", file_name.c_str());
        return false;
    }

    std::getline(user_file, head);

    while(user_file.good()) {

        user_file >> name  >> password >> account;
        created = createUser(name, password, account);
        
        if(!created) {
            fprintf(stderr, "Unable to add user %s\n", name.c_str());
        }
    }

    user_file.close();
    
    return true;
}

      
bool Login::outputCSV() {
    return false;
}