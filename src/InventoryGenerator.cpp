#include "InventoryGenerator.hpp"

InventoryGenerator::InventoryGenerator() {
    id_count = 0;
    factor = 2;
    random = false;
    bad = false;
}

void InventoryGenerator::generateFile(const std::string &file_name, unsigned int unknown, unsigned int non_perishable,
                                      unsigned int perishable) {
    unsigned int i;

    /* Attempt to open file and throw exception if failed */
    file.open(file_name);
    if (!file.is_open()) throw std::string("Failed to open file for writing.");

    for (size_t j = 0; j < columns.size(); ++j) {
        file << columns[j];
        if (j != columns.size() - 1) file << ',';
    }
    file << std::endl;

    /* The following loops:
     * Toggle bad if we've declared random with no bad keys.
     * Generate the entry and print it out.
     */

    for (i = 0; i < unknown; ++i) {
        if (random && bad_keys.empty()) bad = !bad;
        auto entry = generateItem();
        entry->printEntry(file);
    }

    for (i = 0; i < non_perishable; ++i) {
        if (random && bad_keys.empty()) bad = !bad;
        auto entry = generateNonPerishableItem();
        entry->printEntry(file);
    }

    for (i = 0; i < perishable; ++i) {
        if (random && bad_keys.empty()) bad = !bad;
        auto entry = generatePerishableItem();
        entry->printEntry(file);
    }

    file.close();
}

std::shared_ptr<CSVEntry> InventoryGenerator::generateItem() {
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<int> distrib_size(1, 32);
    std::uniform_int_distribution<int> distrib_index(0, 51);
    std::uniform_int_distribution<int> distrib_int(0, 1000);
    std::uniform_int_distribution<int> distrib_keys(0, bad_keys.size() * factor);
    std::uniform_real_distribution<double> distrib_double(0.25, 10000);
    std::shared_ptr<CSVEntry> entry;
    int name_length;
    std::string tmp_name;
    entry = std::make_shared<CSVEntry>();

    /* Generate a random length string and push back that many random chars */
    do {
        name_length = distrib_size(gen);
        for (int i = 0; i < name_length; ++i) {
            tmp_name.push_back(chars[distrib_index(gen)]);
        }

        if (used_names.find(tmp_name) == used_names.end()) {
            used_names.insert(tmp_name);
            entry->name = tmp_name;
            break;
        }
    } while (1);

    /* Set category to undefined, it's not perishable or non-perishable. */
    entry->category = "-1";
    entry->sub_category = "-1";
    entry->expiration_date = "-1";

    /* Generate values; potentially make them bad */

    /* This allows for *some* bad name generation, but not enough.  I'm gonna rewrite this program the next time I'm bored, probably. */
    if (random && isBadKey("name") && distrib_keys(gen) == 0)
        entry->name = *used_names.begin();
    else if (!random && isBadKey("name"))
        entry->name = *used_names.begin();

    entry->quantity = distrib_int(gen);
    if (random && isBadKey("quantity") && distrib_keys(gen) == 0)
        entry->quantity *= -1;
    else if (!random && isBadKey("quantity"))
        entry->quantity *= -1;

    /*  > 0 quantities *can* have backorder, but for the sake of our testing files, we don't want that. */
    if (entry->quantity == 0)
        entry->backorder = distrib_int(gen);
    else
        entry->backorder = 0;

    if (random && isBadKey("backorder") && distrib_keys(gen) == 0)
        entry->backorder *= -1;
    else if (!random && isBadKey("backorder"))
        entry->backorder *= -1;

    entry->id = id_count;
    if (random && isBadKey("id") && distrib_keys(gen) != 0)
        id_count++;
    else if (!random && !isBadKey("id"))
        id_count++;

    entry->sale_price = distrib_double(gen);
    if (random && isBadKey("sale_price") && distrib_keys(gen) == 0)
        entry->sale_price *= -1;
    else if (!random && isBadKey("sale_price"))
        entry->sale_price *= -1;

    std::uniform_real_distribution<double> distrib_cost(0.05, entry->sale_price / 2);
    entry->buy_cost = distrib_cost(gen);
    if (random && isBadKey("buy_cost") && distrib_keys(gen) == 0)
        entry->buy_cost *= -1;
    else if (!random && isBadKey("buy_cost"))
        entry->buy_cost *= -1;

    entry->tax = 0.1;
    if (random && isBadKey("tax") && distrib_keys(gen) == 0)
        entry->tax = -0.1;
    else if (!random && isBadKey("tax"))
        entry->tax = -0.1;

    /* Calculated from other values, doesn't make sense to make "bad" from command
     * line */
    entry->total_price = (entry->tax * entry->sale_price) + entry->sale_price;
    entry->profit = entry->sale_price - entry->buy_cost;

    return entry;
}

std::shared_ptr<CSVEntry> InventoryGenerator::generateNonPerishableItem() {
    auto entry = generateItem();
    entry->category = "NonPerishable";
    return entry;
}

std::shared_ptr<CSVEntry> InventoryGenerator::generatePerishableItem() {
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<int> distrib_month(1, 12);
    std::uniform_int_distribution<int> distrib_day(1, 28);        // let's pretend all months have 28
    std::uniform_int_distribution<int> distrib_year(2023, 2035);  // years chosen for no reason
    std::uniform_int_distribution<int> distrib_keys(0, bad_keys.size() * factor);
    std::stringstream ss;

    /* Generate bad expiration date if told to; otherwise, generate a valid one */
    if (random && isBadKey("expiration_date") && distrib_keys(gen) == 0)
        ss << -1;
    else if (!random && isBadKey("expiration_date"))
        ss << -1;
    else
        ss << distrib_month(gen) << '/' << distrib_day(gen) << '/' << distrib_year(gen);

    auto entry = generateItem();
    entry->category = "Perishable";
    entry->expiration_date = ss.str();

    return entry;
}

void InventoryGenerator::setBadKey(const std::string &key) {
    bad_keys.insert(key);
    bad = true;
}

bool InventoryGenerator::isBadKey(const std::string &key) {
    if (random && bad_keys.empty()) return bad;
    auto it = bad_keys.find(key);
    return !(it == bad_keys.end());
}

void InventoryGenerator::toggleRandom() { random = !random; }

void InventoryGenerator::setRandomFactor(const int &i) { factor = i; }