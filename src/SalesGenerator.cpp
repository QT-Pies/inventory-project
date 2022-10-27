#include "SalesGenerator.hpp"

SalesGenerator::SalesGenerator(const std::string& name) : transactions(0), original_name(name) {
    readInventory();
    parent_name = name.substr(0, name.size() - 4) + "_parent_sales.csv";
    child_name = name.substr(0, name.size() - 4) + "_child_sales.csv";
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

    return true;
}

std::shared_ptr<CSVEntry> SalesGenerator::grabRandomItem() {
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<size_t> distrib_size(0, inventory.size());
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

    for (auto i = 0; i < max; ++i) {
        transactions = i;
        auto transaction = newTransaction();
        auto num_sales = distrib_sales(gen);

        for (auto j = 0; j < num_sales; ++j) {
            auto sale = transaction->addSale(grabRandomItem());
            sale->print(c_file);
        }

        transaction->print(p_file);

    }
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
    std::vector<std::string> names = {"Noah", "Jon", "Jen", "Vincent", "Joseph", "Bob", "David", "Alan",
    "Dave", "Davey", "Dave-Dog", "Jim", "James", "Stephen", "Greg", "Gregg", "Joe", "Vinny", "Jon-Jon",
    "Jen-Jen", "Joe-Joe", "Jim-Plank", "Michael"};
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<size_t> distrib_size(0, names.size());

    return names.at(distrib_size(gen));
}

void MockTransaction::print(std::ostream& out) {
    out << id << ',';
    out << date.year << '/' << date.month << '/' << date.day << ',';
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
    std::uniform_int_distribution<unsigned long> distrib_sold(1, item->quantity / 2);

    num_sold = distrib_sold(gen);

    /* We don't use items with quantity == 0, and the range is 1->quantity, so no fear of < 0. */
    item->quantity -= num_sold;
}

void MockSale::print(std::ostream& out) {
    out << id << ',' << item_id << ',' << num_sold << ',' << sale_price << std::endl;
}