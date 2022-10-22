#include "Item.hpp"

Item::Item(const std::string &nm, const std::string &cat, const std::string &sub_cat, const std::string &qty,
           const std::string &idd, const std::string &price, const std::string &cost, const std::string &tx) {
    bool validated = true;
    

    /* Validate input */
    validated &= setValue("name", nm);
    validated &= setValue("category", cat);
    validated &= setValue("sub_category", sub_cat);
    validated &= setValue("quantity", qty);
    validated &= setValue("id", idd);
    validated &= setValue("sale_price", price);
    validated &= setValue("buy_cost", cost);
    validated &= setValue("tax", tx);

    if (!validated) {
        std::cerr << "Failed to construct Item with given parameters." << std::endl;
    }

    profit = sale_price - buy_cost;
    total_price = sale_price + (tax * sale_price);
}

bool Item::setValue(std::string key, const std::string& value) {
    /* Big try / catch to catch all possible bad_argument exceptions */
    try {
        /* Check if key is any of Item's members */
        if (key == "name") {
            name = value;
            return true;
        } else if (key == "category") {
            category = value;
            return true;
        } else if (key == "sub_category") {
            sub_category = value;
            return true;
        } else if (key == "quantity") {
            quantity = toUnsignedLong(value);
            return true; 
        } else if (key == "id") {
            id = toUnsignedLong(value);
            return true;
        } else if (key == "sale_price") {
            sale_price = toFauxUnsignedDouble(value);
            return true;
        } else if (key == "buy_cost") {
            buy_cost = toFauxUnsignedDouble(value);
            return true;
        } else if (key == "tax") {
            tax = toFauxUnsignedDouble(value);
            return true;
        } else {
            std::cerr << "Could not find key '" << key << "' in Item or any of its inherited class." << std::endl;
            return false;
        }
    } catch (std::invalid_argument& e) {
        /* We don't care about the error message thrown from the helper functions, throw another one. */
        throw std::invalid_argument("Failed to set value '" + value + "' for key '" + key + "' for Item '" + name + "'.");
    }
}