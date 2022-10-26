#include "SalesGenerator.hpp"

SalesGenerator::SalesGenerator(const std::string& name) : original_name(name) {
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