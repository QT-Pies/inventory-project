#include "SalesGenerator.hpp"

SalesGenerator::SalesGenerator(const std::string& name, const std::string& start)
    : transactions(0), original_name(name), last_date(start) {
    readInventory();
    parent_name = name.substr(0, name.size() - 4) + "_parent_sales.csv";
    child_name = name.substr(0, name.size() - 4) + "_child_sales.csv";

    /* Lastly set how many days are in a month. */
    if (curr_y % 4 == 0) {
        days_in_month = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    } else {
        days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    }

    time_t current_date;
    current_date = time(0);
    tm* ltm = localtime(&current_date);
    curr_y = 1900 + ltm->tm_year;
    curr_m = 1 + ltm->tm_mon;
    curr_d = ltm->tm_mday;
}

bool SalesGenerator::readInventory() {
    std::ifstream inventory_file;
    std::string line;

    inventory_file.open(original_name);

    /* Verify able to open file */
    if (!inventory_file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return false;
    }

    /* Skip first line */
    std::getline(inventory_file, line);

    /* Read in all the entries from the inventory file */
    while (std::getline(inventory_file, line)) {
        auto entry = std::make_shared<CSVEntry>(line);
        inventory.push_back(entry);
    }

    inventory_file.close();
    return true;
}

std::shared_ptr<CSVEntry> SalesGenerator::grabRandomItem() {
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<size_t> distrib_size(0, inventory.size() - 1);
    std::shared_ptr<CSVEntry> rv;

    /* Grab an item we can sell, i.e, it's quantity > 0.*/
    do {
        rv = inventory.at(distrib_size(gen));
    } while (rv->quantity == 0);

    return rv;
}

std::shared_ptr<MockTransaction> SalesGenerator::newTransaction() {
    auto rv = std::make_shared<MockTransaction>(transactions);
    return rv;
}

void SalesGenerator::generateTransactions(unsigned long max) {
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<unsigned long> distrib_sales(1, MAX_SALES_PER_TRANSACTION);
    std::ofstream p_file(parent_name);
    std::ofstream c_file(child_name);

    p_file << "Sale_ID, Date, Total_Price, Quantity_of_Items, Buyer, Seller\n";
    c_file << "Sale_ID, Item_ID, Quantity_Sold, Sale_Price\n";

    transactions = 1;

    for (unsigned long i = 0; i < max; ++i) {
        auto transaction = newTransaction();
        auto num_sales = distrib_sales(gen);

        for (unsigned long j = 0; j < num_sales; ++j) {
            auto sale = transaction->addSale(grabRandomItem());
            sale->print(c_file);
        }

        transaction->date = last_date;
        transaction->print(p_file);
        nextDate();

        if (last_date.year == curr_y && last_date.month == curr_m && last_date.day > curr_d) {
            std::cout << "Only able to generate " << i + 1 << " sales" << std::endl;
            break;
        }
    }

    p_file.close();
    c_file.close();
}

void SalesGenerator::nextDate() {
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<int> distrib_date(0, 1);
    Date tmp(last_date);

    /* If we randomly generated a 1, keep the current date, increment transactions. */
    if (distrib_date(gen)) {
        transactions++;
        return;
    }

    /* Otherwise, move the date and reset the transaction counter to 1. */

    tmp.day++;

    /* Move month */
    if ((int)tmp.day > days_in_month[tmp.month - 1]) {
        tmp.month++;
        tmp.day = 1;
        if (tmp.month > 12) {
            tmp.year++;
            tmp.month = 1;
        }
    }

    transactions = 1;
    last_date = tmp;
}

MockTransaction::MockTransaction(unsigned long idd) : id(idd), total_price(0), quantity_of_items(0) {
    buyer = getRandomName();
    seller = getRandomName();
}

std::shared_ptr<MockSale> MockTransaction::addSale(std::shared_ptr<CSVEntry> item) {
    auto sale = std::make_shared<MockSale>(item, id);

    sale->setNumSold();

    quantity_of_items++;
    total_price += (sale->sale_price * sale->num_sold);

    return sale;
}

std::string MockTransaction::getRandomName() {
    std::vector<std::string> names = {"Noah", "Jon",   "Jen",      "Vincent", "Joseph",  "Bob",       "David",  "Alan",
                                      "Dave", "Davey", "Dave-Dog", "Jim",     "James",   "Stephen",   "Greg",   "Gregg",
                                      "Joe",  "Vinny", "Jon-Jon",  "Jen-Jen", "Joe-Joe", "Jim-Plank", "Michael"};
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<size_t> distrib_size(0, names.size() - 1);

    return names.at(distrib_size(gen));
}

void MockTransaction::print(std::ostream& out) {
    out << id << ',';
    out << date.month << '/' << date.day << '/' << date.year << ',';
    out << total_price << ',' << quantity_of_items << ',';
    out << buyer << ',' << seller << std::endl;
}

MockSale::MockSale(std::shared_ptr<CSVEntry> c_item, unsigned long idd) : item(c_item), id(idd) {
    item_id = item->id;
    sale_price = item->sale_price;
}

void MockSale::setNumSold() {
    std::random_device rand;
    std::mt19937 gen(rand());
    unsigned long q;

    if (item->quantity / 2 <= 3) {
        q = item->quantity / 2;
    } else {
        q = 3;
    }

    std::uniform_int_distribution<unsigned long> distrib_sold(1, q);

    num_sold = distrib_sold(gen);
}

void MockSale::print(std::ostream& out) {
    out << id << ',' << item_id << ',' << num_sold << ',' << sale_price << std::endl;
}