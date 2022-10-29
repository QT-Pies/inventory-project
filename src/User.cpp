#include "User.hpp"

User::User(const std::string username, const std::string pswd, const std::string acc_type) {
    int perm_level = getPermissionLevel(acc_type);

    if (perm_level == -1) return;

    name = username;
    password = pswd;
    account_type = acc_type;
    permission = perm_level;
}

bool User::updateAccount(const std::string account) {
    int perm_level;

    perm_level = getPermissionLevel(account);

    if (perm_level == -1) return false;

    permission = perm_level;
    account_type = account;

    return true;
}

int User::getPermissionLevel(std::string account) {
    int p;

    if (account == "employee") {
        p = 1;
    } else if (account == "manager") {
        p = 3;
    } else if (account == "owner") {
        p = 5;
    } else {
        Logger::logError("No such account type '%s'.", account.c_str());
        p = -1;
    }

    return p;
}