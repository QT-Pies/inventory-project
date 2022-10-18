#include "NonPerishableItem.hpp"

NonPerishableItem::NonPerishableItem(const std::string &nm, const std::string &cat, const std::string &sub_cat,
                                     unsigned long qty, unsigned long idd, double price, double cost, double tx)
    : Item(nm, cat, sub_cat, qty, idd, price, cost, tx) {}

void NonPerishableItem::print() {
    std::cout << std::left << std::setw(7) << id << std::left << std::setw(40) << name << std::left << std::setw(17)
              << category << std::left << std::setw(10) << quantity << std::left << std::setw(15) << buy_cost
              << std::left << std::setw(15) << sale_price << std::left << std::setw(15) << tax * sale_price << std::left
              << std::setw(15) << total_price << std::left << std::setw(10) << profit << std::left << std::setw(10)
              << "-1" << std::endl;
}

void NonPerishableItem::printCSV(std::ofstream &file) {
    file << name << ",";
    file << id << ",";
    file << category << ",";
    file << sub_category << ",";
    file << quantity << ",";
    file << sale_price << ",";
    file << tax << ",";
    file << total_price << ",";
    file << buy_cost << ",";
    file << profit << ",";
    file << "-1";
}

NonPerishableItem::~NonPerishableItem() {}
