#include "User.hpp"

User::User(const std::string username, const std::string pswd, const std::string acc_type) {
    name = username;
    password = pswd;
    account_type = acc_type;

    if (acc_type == "owner") permission = 5;
    if (acc_type == "manager") permission = 3;
    if (acc_type == "employee") permission = 1;
}