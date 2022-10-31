#include "CSVEntry.hpp"

CSVEntry::CSVEntry() {}

CSVEntry::CSVEntry(std::string line) {
    std::stringstream input(line);
    std::string tmp;

    /* Read input */
    std::getline(input, name, ',');

    std::getline(input, tmp, ',');
    id = std::stoi(tmp);

    std::getline(input, category, ',');
    std::getline(input, sub_category, ',');

    std::getline(input, tmp, ',');
    quantity = std::stoi(tmp);
    std::getline(input, tmp, ',');
    backorder = std::stoi(tmp);
    std::getline(input, tmp, ',');
    sale_price = std::stod(tmp);
    std::getline(input, tmp, ',');
    tax = std::stod(tmp);
    std::getline(input, tmp, ',');
    total_price = std::stod(tmp);
    std::getline(input, tmp, ',');
    buy_cost = std::stod(tmp);
    std::getline(input, tmp, ',');
    profit = std::stod(tmp);
    std::getline(input, expiration_date, ',');
}

void CSVEntry::printEntry(std::ostream &out) {
    out << name << ',';
    out << id << ',';
    out << category << ',';
    out << sub_category << ',';
    out << quantity << ',';
    out << backorder << ',';
    out << std::setprecision(2) << std::fixed << std::showpoint << sale_price << ',';
    out << tax << ',';
    out << total_price << ',';
    out << buy_cost << ',';
    out << profit << ',';
    out << expiration_date << std::endl;
}