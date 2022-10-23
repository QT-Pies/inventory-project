#include "Login.hpp"

Login::Login() { /* does nothing */
}

Login::~Login() {
    /* no deletion required*/
    outputCSV();
}

bool Login::createUser(const std::string name, const std::string password, const std::string account) {
    if (account != "manager" && account != "owner" && account != "employee") {
        fprintf(stderr, "Invalid account type\n");
        return false;
    }

    if (users.find(name) == users.end()) {
        std::shared_ptr<User> new_user = std::make_shared<User>(name, password, account);
        users[name] = new_user;
    } else {
        fprintf(stderr, "User %s already exists\n", name.c_str());
        return false;
    }

    return true;
}

std::shared_ptr<User> Login::userInput() {
    char argument;
    std::string category, name, password, account;

    while (true) {
        std::cout << "\n(L)ogin or (C)reate User: ";
        std::cin >> argument;

        switch (argument) {
            case 'l':
            case 'L': {
                std::cin.clear();
                std::cin.ignore(10000, '\n');

                std::cout << "Name: ";
                std::cin >> name;
                std::cout << "Password: ";
                std::cin >> password;

                auto user = verifyUser(name, password);
                if (user != NULL) {
                    return user;
                } else {
                    fprintf(stderr, "Invalid username or password\n");
                    break;
                }
                break;
            }
            case 'c':
            case 'C': {
                std::cin.clear();
                std::cin.ignore(10000, '\n');

                std::cout << "Name: ";
                std::cin >> name;
                std::cout << "Password: ";
                std::cin >> password;
                std::cout << "Account Type: ";
                std::cin >> account;
                createUser(name, password, account);
                break;
            }
            default:
                break;
        }

        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return NULL;
}

bool Login::readCSV() {
    std::string head, name, password, account;
    bool created;
    std::ifstream user_file(file_name);

    if (!user_file.is_open()) {
        fprintf(stderr, "Unable to open %s\n", file_name.c_str());
        return false;
    }

    std::getline(user_file, head);

    while (user_file.peek() != EOF) {
        getline(user_file, name, ',');
        getline(user_file, password, ',');
        getline(user_file, account, '\n');
        created = createUser(name, password, account);

        if (!created) {
            fprintf(stderr, "Unable to add user %s\n", name.c_str());
        }
    }

    user_file.close();

    return true;
}

bool Login::outputCSV() {
    std::ofstream file;

    file.open(file_name);

    if (!file.is_open()) {
        fprintf(stderr, "File %s is unable to open", file_name.c_str());
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