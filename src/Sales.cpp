#include "Sales.hpp"

Sale::Sale(const unsigned long sid, const unsigned long iid, const unsigned long ns, const double sp)
    : sale_id(sid), item_id(iid), num_sold(ns), sale_price(sp) {}

Sale::~Sale() {}

Transaction::Transaction(const unsigned long sid, const std::string b, const std::string s, const unsigned int m,
                         const unsigned int d, const unsigned int y)
    : sale_id(sid), month(m), day(d), year(y), buyer(b), seller(s) {
    total_price = 0;
    num_sales = 0;
    date = std::to_string(m) + '/' + std::to_string(d) + '/' + std::to_string(y);
    unique_transaction_id = std::to_string(sid) + std::to_string(m) + std::to_string(d) + std::to_string(y);
}

Transaction::~Transaction() {}

bool Transaction::addSale(const unsigned long sid, const unsigned long iid, const unsigned long ns, const double sp) {
    // making sure items are sold in the sale, if not the sale is considered invalid
    if (ns == 0) {
        Logger::logError("Invalid input -- verify amount sold is > 0.  Continuing to read.");
        return false;
    }
    auto new_sale = std::make_shared<Sale>(sid, iid, ns, sp);
    sales.push_back(new_sale);
    total_price += (ns * sp);
    num_sales++;
    new_sale->unique_sale_id = unique_transaction_id + "_" + std::to_string(num_sales);
    return true;
}

bool Transaction::removeSale(const unsigned long sid, const unsigned long iid, const unsigned long ns,
                             const double sp) {
    unsigned int i;

    for (i = 0; i < sales.size(); i++) {
        if (sales[i]->sale_id == sid && sales[i]->item_id == iid && sales[i]->num_sold == ns &&
            sales[i]->sale_price == sp) {
            sales[i] = NULL;
            num_sales--;
            return true;
        }
    }

    return false;
}

void Transaction::processTransaction(std::shared_ptr<ActiveInventory> active_inv) {
    unsigned int i;
    unsigned long amount;

    for (i = 0; i < sales.size(); i++) {
        auto s = sales[i];
        auto item = active_inv->searchById(s->item_id);

        if (item == NULL) {
            Logger::logError("Invalid item id %lu. Continuing to process.", s->item_id);
        } else {
            if (item->quantity < s->num_sold) {
                amount = s->num_sold - item->quantity;
                item->quantity = 0;
                item->backorder += amount;

            } else {
                item->quantity -= s->num_sold;
            }
        }
    }
}

SaleList::SaleList() {
    std::make_unique<std::map<
        unsigned int, std::map<unsigned int, std::map<unsigned int, std::vector<std::shared_ptr<Transaction> > > > > >(
        transaction_by_date);
    std::make_unique<std::vector<std::shared_ptr<Transaction> > >(transaction_by_order);
    curr_sale_id = 1;
    curr_transaction = 0;
}

SaleList::~SaleList() {}

void SaleList::userTransaction(const unsigned long sid, const std::string b, const std::string s) {
    time_t current_date;
    unsigned int m, d, y;

    current_date = time(0);
    tm *ltm = localtime(&current_date);
    m = 1 + ltm->tm_mon;
    d = ltm->tm_mday;
    y = 1900 + ltm->tm_year;
    newTransaction(sid, b, s, m, d, y);
}

void SaleList::newTransaction(const unsigned long sid, const std::string b, const std::string s, const unsigned int m,
                              const unsigned int d, const unsigned int y) {
    auto new_transaction = std::make_shared<Transaction>(sid, b, s, m, d, y);
    transaction_by_order.push_back(new_transaction);
    transaction_by_date[m][d][y].push_back(new_transaction);
    curr_transaction = transaction_by_order.size() - 1;
}

bool SaleList::loadSales(const std::string file) {
    std::ifstream p_fin, c_fin;
    std::string p_line, c_line;
    std::string s_id, s_id_check, i_id, item_quantity, sold_quantity;
    std::string m, d, y;
    unsigned int curr_m, curr_d, curr_y, i;
    std::string tot_price, i_price;
    std::string b, s;
    time_t current_date;

    // getting current date to check if transactions have been added on the same day
    current_date = time(0);
    tm *ltm = localtime(&current_date);
    curr_m = 1 + ltm->tm_mon;
    curr_d = ltm->tm_mday;
    curr_y = 1900 + ltm->tm_year;

    // assuming all files end in .csv
    parent_file = file.substr(0, file.size() - 4) + "_parent_sales.csv";
    child_file = file.substr(0, file.size() - 4) + "_child_sales.csv";

    p_fin.open(parent_file.c_str());
    if (!p_fin.is_open()) {
        Logger::logWarn("Unable to open Sales parent file '%s'.", parent_file.c_str());
        return false;
    }
    c_fin.open(child_file.c_str());
    if (!c_fin.is_open()) {
        Logger::logWarn("Unable to open Sales child file '%s'.", child_file.c_str());
        return false;
    }

    getline(p_fin, p_line);
    getline(c_fin, c_line);
    if (p_line != "Sale_ID, Date, Total_Price, Quantity_of_Items, Buyer, Seller") {
        Logger::logTrace("Expected: %s\nReceived: %s", "Sale_ID, Date, Total_Price, Quantity_of_Items, Buyer, Seller",
                         p_line.c_str());
        Logger::logWarn("Invalid Sales parent file -- Continuing without loading Sales.");
        return false;
    }
    if (c_line != "Sale_ID, Item_ID, Quantity_Sold, Sale_Price") {
        Logger::logTrace("Expected: %s\nReceived:%s", "Sale_ID, Item_ID, Quantity_Sold, Sale_Price", c_line.c_str());
        Logger::logWarn("Invalid Sales child file -- Continuing without loading Sales.");
        return false;
    }

    while (p_fin.good()) {
        getline(p_fin, s_id, ',');
        if (!p_fin.good()) break;
        getline(p_fin, m, '/');
        getline(p_fin, d, '/');
        getline(p_fin, y, ',');
        getline(p_fin, tot_price, ',');
        getline(p_fin, item_quantity, ',');
        getline(p_fin, b, ',');
        getline(p_fin, s, '\n');

        // note total price and item quantity are automatically set when newTransaction is called
        newTransaction(stoul(s_id), b, s, stoul(m), stoul(d), stoul(y));
        // When items are saved to the file, they should be orginized in order from oldest to newest so it can be read
        // like this.
        for (i = 0; i < stoul(item_quantity); i++) {
            getline(c_fin, s_id_check, ',');
            getline(c_fin, i_id, ',');
            getline(c_fin, sold_quantity, ',');
            getline(c_fin, i_price, '\n');
            if (stoul(s_id_check) == stoul(s_id))
                transaction_by_order[curr_transaction]->addSale(stoul(s_id_check), stoul(i_id), stoul(sold_quantity),
                                                                stod(i_price));
        }
        // sale_id is based on the day, so if previous sales have been added today, the sale Id must account for it
        if (stoul(m) == curr_m && stoul(d) == curr_d && stoul(y) == curr_y) {
            curr_sale_id = stoul(s_id) + 1;
        }
    }

    p_fin.close();
    c_fin.close();
    return true;
}

bool SaleList::save() {
    std::ofstream p_fout, c_fout;
    unsigned int i, j;

    p_fout.open(parent_file.c_str());
    if (!p_fout.is_open()) {
        Logger::logFatal("Unable to save Sales parent file -- Sales save is aborted, and sales will be lost.");
        return false;
    }
    c_fout.open(child_file.c_str());
    if (!c_fout.is_open()) {
        Logger::logFatal("Unable to save Sales child file -- Sales save is aborted, and sales will be lost.");
        return false;
    }
    p_fout << "Sale_ID, Date, Total_Price, Quantity_of_Items, Buyer, Seller\n";
    c_fout << "Sale_ID, Item_ID, Quantity_Sold, Sale_Price\n";

    if (transaction_by_order.empty() != true) {
        for (i = 0; i <= curr_transaction; i++) {
            p_fout << transaction_by_order[i]->sale_id << ',' << transaction_by_order[i]->date << ','
                   << transaction_by_order[i]->total_price << ',' << transaction_by_order[i]->num_sales << ','
                   << transaction_by_order[i]->buyer << ',' << transaction_by_order[i]->seller << std::endl;
            for (j = 0; j < transaction_by_order[i]->num_sales; j++) {
                if (transaction_by_order[i]->sales[j] != NULL) {
                    c_fout << transaction_by_order[i]->sales[j]->sale_id << ','
                           << transaction_by_order[i]->sales[j]->item_id << ','
                           << transaction_by_order[i]->sales[j]->num_sold << ','
                           << transaction_by_order[i]->sales[j]->sale_price << std::endl;
                }
            }
        }
    }

    p_fout.close();
    c_fout.close();

    Logger::logInfo("Sales parent file written to '%s'.", parent_file.c_str());
    Logger::logInfo("Sales child file written to '%s'.", child_file.c_str());

    return true;
}

void SaleList::print() {
    unsigned int i, j;

    if (transaction_by_order.empty() != true) {
        for (i = 0; i <= curr_transaction; i++) {
            std::cout << "Transaction #" << transaction_by_order[i]->sale_id << " | " << transaction_by_order[i]->date
                      << " | "
                      << "Total Price: " << transaction_by_order[i]->total_price << std::endl;
            for (j = 0; j < transaction_by_order[i]->num_sales; j++) {
                if (transaction_by_order[i]->sales[j] != NULL) {
                    std::cout << "ItemID: " << transaction_by_order[i]->sales[j]->item_id << " | "
                              << "Quantity Sold: " << transaction_by_order[i]->sales[j]->num_sold << " | "
                              << "Item Price: " << transaction_by_order[i]->sales[j]->sale_price << std::endl;
                }
            }
        }
    }
}
