#include "Sales.hpp"
    // sale_id | item_id | num_sold | sale_price
Sale::Sale(const unsigned long sid, const unsigned long iid, const unsigned long ns, const double sp)
    : sale_id(id), item_id(iid), num_sold(ns), sale_price(sp) {
}

Sale::~Sale() {}

Transaction::Transaction(const unsigned long sid, const std::string b, const std::string s)
    : sale_id(sid), buyer(b), seller(s) {
    total_price = 0;
    num_sales = 0;
    // set date here, will have to adjust it so be prepared.

}

Transaction::~Transaction() {}

bool Transaction::add_sale(const unsigned long sid, const unsigned long iid, const unsigned long ns, const double sp) {
    if(sid == 0 || iid == 0 || ns == 0){
        std::cerr << "Invalid input. Make sure Sale ID, Item ID, and amount sold are greater than 0. Continuing to read\n";
        return false;
    }
    auto new_sale = std::make_shared<Sale>(sid, iid, ns, sp);
    sales.push_back(new_sale);
    total_price += (ns * sp);
    num_sales++;
    return true;
}
















SaleList::SaleList(const std::string f) {
    // change to where te files are the baised on the given file name, then maybe just add _parent and _child, use substring
    parent_file = "Parrent_Sales.csv";
    child_file = "Child_Sales.csv";
}

bool SaleList::add_transaction(const unsigned long sid, const std::string b, const std::string s) {
    if (sid == 0 || b == "" || s == "") {
        std::cerr << "Failed to read Sales Input. Note that the Sales ID"
                     "and a Date and Buyer must be given.\nContinuing to read.";
        return false;
    }
    // get date here, then put the new transaction in the appropriate place based on the date
    auto new_transaction = std::make_shared<Transaction>(sid, b, s);
    return true;
}

/*
 * Creates a new file with the propper starting format.
 */
bool SaleList::newFile() {
    std::ofstream fout;

    fout.open(parent_file.c_str());
    if (!fout.is_open()) return false;
    fout << "Sale_ID, Date, Total_Price, Amount_of_Items, Buyer, Seller";
    fout.close();

    fout.open(child_file.c_str());
    if (!fout.is_open()) return false;
    fout << "Sale_ID, Item_ID, Quantity_Sold, Sale_Price";
    fout.close();
    return true;
}

bool SaleList::load() {
    std::ifstream fpin, fcin;
    std::string line;

    unsigned long id;
    unsigned long sn;
    char d[20];
    unsigned long as;
    double sp;
    double t;
    char b[50];
    char s[50];

    fpin.open(parent_file.c_str());
    if (!fpin.is_open()) return false;
    std::getline(fpin, line);
    if (line != "Sale_ID, Date, Total_Price, Amount_of_Items, Buyer, Seller") return false;

    while (!(fpin.eof())) {
        std::getline(fpin, line);
        sscanf(line.c_str(), "%lu,%lu,%s,%lu,%lf,%lf,%s,%s", &id, &sn, d, &as, &sp, &t, b, s);
        if (!addSale(id, sn, d, as, sp, t, b, s)) {
            std::cerr << "FILE CURRUPTION DETECTED in File: " << parent_file << std::endl;
            return false;
        }
        offset++;
    }
    fpin.close();
    return true;
}

bool SaleList::save() {
    std::ofstream fout;
    unsigned int i;

    fout.open(file_name.c_str(), std::ios::app);
    if (!fout.is_open()) return false;

    for (i = offset; i < sales.size(); i++) {
        fout << std::endl
             << sales[i]->identification << "," << sales[i]->sale_number << "," << sales[i]->date << ","
             << sales[i]->amount_sold << "," << sales[i]->sale_price << "," << sales[i]->tax << "," << sales[i]->buyer
             << "," << sales[i]->seller;
    }
    fout.close();
    return true;
}
