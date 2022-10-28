#include "User.hpp"

User::User(const std::string username, const std::string pswd, const std::string acc_type) {
    if (acc_type == "employee") permission = 1;
    if (acc_type == "manager") permission = 3;
    if (acc_type == "owner") permission = 5;

    name = username;
    password = pswd;
    account_type = acc_type;
}

bool User::updateAccount(const std::string account) {
    if (account != "owner" && account != "employee" && account != "manager") return false;

    account_type = account;

    if (account == "employee") permission = 1;
    if (account == "manager") permission = 3;
    if (account == "owner") permission = 5;

    return true;
}