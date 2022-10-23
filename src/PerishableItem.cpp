#include "PerishableItem.hpp"

PerishableItem::PerishableItem(const std::string &nm, const std::string &cat, const std::string &sub_cat,
                               const std::string &qty, const std::string &idd, const std::string &price,
                               const std::string &cost, const std::string &tx, const std::string &exp)
    : Item(nm, cat, sub_cat, qty, idd, price, cost, tx) {
    setValue("expiration_date", exp);
}

void PerishableItem::print() {
    std::cout << std::left << std::setw(7) << id << std::left << std::setw(40) << name << std::left << std::setw(17)
              << category << std::left << std::setw(10) << quantity << std::left << std::setw(15) << buy_cost
              << std::left << std::setw(15) << sale_price << std::left << std::setw(15) << tax * sale_price << std::left
              << std::setw(15) << total_price << std::left << std::setw(10) << profit << std::left << std::setw(10)
              << expiration_date.string_date << std::endl;
}

void PerishableItem::setValue(std::string key, const std::string &value) {
    try {
        if (key == "expiration_date") {
            expiration_date = Date(value);
        } else {
            Item::setValue(key, value);
        }
    } catch (std::invalid_argument &e) {
        /* We don't care about the error message thrown from the helper functions, throw another one that's more useful
         * to the end user. */
        throw std::invalid_argument("Failed to set value '" + value + "' for key '" + key + "' for PerishableItem '" +
                                    name + "'.");
    }
}

void PerishableItem::printCSV(std::ofstream &file) {
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
    file << expiration_date.string_date;
}

PerishableItem::~PerishableItem() {}
