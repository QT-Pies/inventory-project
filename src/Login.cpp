#include "Login.hpp"

Login::Login() { readCSV(); }

Login::~Login() { /* no deletion required*/
}

bool Login::createUser(const std::string name, const std::string password, std::string account) {
    lowerCaseString(account);

    if (account != "manager" && account != "owner" && account != "employee") {
        Logger::logError("Invalid account type '%s'", account.c_str());
        return false;
    }
    if (users.find(name) == users.end()) {
        std::shared_ptr<User> new_user = std::make_shared<User>(name, password, account);
        users[name] = new_user;
    } else {
        Logger::logError("User '%s' already exists.", name.c_str());
        return false;
    }

    return true;
}

std::shared_ptr<User> Login::userInput() {
    char argument;
    std::string category, name, password;

    while (true) {
        std::cout << "\n(L)ogin, (C)reate User, or (Q)uit: ";
        std::cin >> argument;

        switch (argument) {
            case 'l':
            case 'L': {
                std::cin.clear();
                std::cin.ignore(10000, '\n');

                std::cout << "Name: ";
                getline(std::cin, name);
                std::cout << "Password: ";
                getline(std::cin, password);

                auto user = verifyUser(name, password);
                if (user != NULL) {
                    return user;
                } else {
                    // I didn't replace this because I think it makes sense to give the user normal feedback here, so it
                    // should to stdout instead of stderr.
                    printf("Invalid username or password\n");
                    Logger::logTrace("Failed login to User '%s'.", name.c_str());
                    break;
                }
                break;
            }
            case 'c':
            case 'C': {
                std::cin.clear();
                std::cin.ignore(10000, '\n');

                std::cout << "Name: ";
                getline(std::cin, name);
                std::cout << "Password: ";
                getline(std::cin, password);
                createUser(name, password);
                break;
            }
            case 'q':
            case 'Q': {
                printf("Exiting InventoryManager.\n");
                return NULL;
            }
            default:
                break;
        }
    }
    return NULL;
}

bool Login::readCSV() {
    std::string head, name, password, account;
    bool created;
    std::ifstream user_file(file_name);

    if (!user_file.is_open()) {
        Logger::logWarn("Unable to open '%s'.", file_name.c_str());
        return false;
    }

    std::getline(user_file, head);

    while (user_file.peek() != EOF) {
        getline(user_file, name, ',');
        getline(user_file, password, ',');
        getline(user_file, account, '\n');
        created = createUser(name, password, account);

        if (!created) {
            Logger::logError("Unable to add user '%s'.", name.c_str());
        }
    }

    user_file.close();

    return true;
}

bool Login::outputCSV() {
    std::ofstream file;

    file.open(file_name);

    if (!file.is_open()) {
        Logger::logFatal("Unable to open file '%s'.  User accounts will be lost!", file_name.c_str());
        return false;
    }

    file << "NAME,PASSWORD,ACCOUNT" << std::endl;

    for (auto mit = users.begin(); mit != users.end(); mit++) {
        file << mit->second->name << "," << mit->second->password << "," << mit->second->account_type << std::endl;
    }

    file.close();

    return true;
}

std::shared_ptr<User> Login::verifyUser(const std::string name, const std::string password) {
    auto it = users.find(name);

    if (it != users.end()) {
        if (it->second->password == password) {
            return it->second;
        }
    } else {
        return NULL;
    }

    return NULL;
}

bool Login::changePermission(std::string username, std::string account, std::shared_ptr<User> current_user) {
    int p;

    p = current_user->getPermissionLevel(account);

    if (p == -1) return false;

    auto it = users.find(username);
    if (it != users.end()) {
        /* if the current_user's permissions are greater than or equal to the account it is updating too and
           the current_user's permissions are greater then the user account is is updating then update
           */
        if (current_user->permission >= p && current_user->permission > it->second->permission) {
            if (it->second->updateAccount(account)) {
                return true;
            } else {
                return false;
            }
        } else {
            Logger::logWarn("User %s does not have the required permissions to change permissions of user '%s'.",
                            current_user->name.c_str(), username.c_str());
        }
    }

    return false;
}
