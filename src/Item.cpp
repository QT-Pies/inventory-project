#include "Item.hpp"

Item::Item(const std::string &nm, const std::string &cat, const std::string &sub_cat, const std::string &qty,
           const std::string &back, const std::string &idd, const std::string &price, const std::string &cost,
           const std::string &tx) {
    /* Validate input */
    setValue("name", nm);
    setValue("category", cat);
    setValue("sub_category", sub_cat);
    setValue("quantity", qty);
    setValue("backorder", back);
    setValue("id", idd);
    setValue("sale_price", price);
    setValue("buy_cost", cost);
    setValue("tax", tx);

    profit = sale_price - buy_cost;
    total_price = sale_price + (tax * sale_price);
}

void Item::setValue(std::string key, const std::string &value) {
    /* Big try / catch to catch all possible bad_argument exceptions */
    try {
        /* Check if key is any of Item's members */
        if (key == "name") {
            name = value;
        } else if (key == "category") {
            category = value;
        } else if (key == "sub_category") {
            sub_category = value;
        } else if (key == "quantity") {
            quantity = toUnsignedLong(value);
        } else if (key == "backorder") {
            backorder = toUnsignedLong(value);
        } else if (key == "id") {
            id = toUnsignedLong(value);
        } else if (key == "sale_price") {
            sale_price = toFauxUnsignedDouble(value);
        } else if (key == "buy_cost") {
            buy_cost = toFauxUnsignedDouble(value);
        } else if (key == "tax") {
            tax = toFauxUnsignedDouble(value);
        } else {
            /* This throw will get overwritten, but still throw. */
            throw std::invalid_argument("Could not find key '" + key +
                                        "' in Item or the subclass you called this method on.");
        }
    } catch (std::invalid_argument &e) {
        /* We don't care about the error message thrown from the helper functions, throw another one that's more useful
         * to the end user. */
        throw std::invalid_argument("Failed to set value '" + value + "' for key '" + key + "' for Item '" + name +
                                    "'.");
    }
}