#include "SalesGenerator.hpp"

SalesGenerator::SalesGenerator(const std::string& name) : original_name(name) {

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