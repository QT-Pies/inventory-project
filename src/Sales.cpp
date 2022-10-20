#include "Sales.hpp"

Sale::Sale(const unsigned long id, const unsigned long sn, const std::string &d, const unsigned long as,
           const double sp, const double t, const std::string &b, const std::string &s)
    : identification(id), sale_number(sn), date(d), amount_sold(as), sale_price(sp), tax(t), buyer(b), seller(s) {
    total_price = sale_price + (tax * sale_price);
}

Sale::~Sale() {}

SaleList::SaleList() {
    parent_file = "Parrent_Sales.csv";
    child_file = "Child_Sales.csv";
    offset = 0;
}

bool SaleList::addSale(const unsigned long id, const unsigned long sn, const std::string &d, const unsigned long as,
                       const double sp, const double t, const std::string &b, const std::string &s) {
    if (id == 0 || sn == 0 || as == 0 || sp == 0 || d == "" || b == "") {
        std::cerr << "Failed to read Sales Input. Note that the ID, Sales Number, "
                     "and Sales Price cannot be 0 and a Date and Buyer must be "
                     "given.\nContinuing to read.";
        return false;
    }

    auto new_sale = std::make_shared<Sale>(id, sn, d, as, sp, t, b, s);
    sales.push_back(new_sale);
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
    fout << "Sale_ID, Item_ID, Quantity_Sold, Sale_Price, Tax";
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
