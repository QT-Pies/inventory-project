#include "Sales.hpp"
    // sale_id | item_id | num_sold | sale_price
Sale::Sale(const unsigned long sid, const unsigned long iid, const unsigned long ns, const double sp)
    : sale_id(sid), item_id(iid), num_sold(ns), sale_price(sp) {
}

Sale::~Sale() {}

Transaction::Transaction(const unsigned long sid, const std::string b, const std::string s, 
                         const unsigned int y, const unsigned int m, const unsigned int d)
    : sale_id(sid), buyer(b), seller(s) {
    total_price = 0;
    num_sales = 0;
}

Transaction::~Transaction() {}

bool Transaction::addSale(const unsigned long sid, const unsigned long iid, const unsigned long ns, const double sp) {
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





SaleList::SaleList() {
    // change to where te files are the based on the given file name, then maybe just add _parent and _child, use substring
    // will assume that the last 4 characters in the string are .csv, unless file name is >=4 characters long
    std::make_unique <std::map<unsigned int, std::map<unsigned int, std::map<unsigned int, std::shared_ptr<Transaction> > > > >(transaction_by_date);
    parent_file = "Parrent_Sales.csv";
    child_file = "Child_Sales.csv";
    curr_sale_id = 1;
}

SaleList::~SaleList() {}

// uses current time to set date feilds
bool SaleList::addTransaction(const unsigned long sid, const std::string b, const std::string s) {
    time_t current_date;
    unsigned int y, m, d;

    
    current_date = time(0);
    tm *ltm = localtime(&current_date);
    y = 1900 + ltm->tm_year;
    m = 1 + ltm->tm_mon;
    d = ltm->tm_mday;

    if(loadTransaction(sid, b, s, y, m, d)) return true;
    else return false;
}
// reads in input to set date feilds, based on csv files
bool SaleList::loadTransaction(const unsigned long sid, const std::string b, const std::string s, 
                               const unsigned int y, const unsigned int m, const unsigned int d) {
    std::map<unsigned int, std::map<unsigned int, std::map<unsigned int, std::shared_ptr<Transaction> > > >::iterator yit;
    std::map<unsigned int, std::map<unsigned int, std::shared_ptr<Transaction> > >::iterator mit;
    std::map<unsigned int, std::shared_ptr<Transaction> >::iterator dit;

    if (sid == 0 || b == "" || s == "") {
        std::cerr << "Failed to read Sales Input. Note that the Sales ID"
                     "and a Date and Buyer must be given.\nContinuing to read.";
        return false;
    }
    auto new_transaction = std::make_shared<Transaction>(sid, b, s, y, m, d);
    return true;

    //transaction_by_date


}

/*
 * Creates a new file with the propper starting format.
 */
bool SaleList::newFile() {
    std::ofstream fout;

    fout.open(parent_file.c_str());
    if (!fout.is_open()) return false;
    fout << "Sale_ID, Date, Total_Price, Quantity_of_Items, Buyer, Seller";
    fout.close();

    fout.open(child_file.c_str());
    if (!fout.is_open()) return false;
    fout << "Sale_ID, Item_ID, Quantity_Sold, Sale_Price";
    fout.close();
    return true;
}

bool SaleList::load(const std::string file) {
    (void) file;
    // ALSO SET PARENT AND CHILD FILE NAMES HERE, will also have to change newFile to do this
    // std::ifstream p_fin, c_fin;
    // std::string line;

    // unsigned long id;
    // // unsigned long sn;
    // //char d[20];
    // //unsigned long as;
    // //double sp;
    // //double t;
    // char b[50];
    // char s[50];
    // unsigned int y, m, d;

    // p_fin.open(parent_file.c_str());
    // if (!p_fin.is_open()) return false;
    // std::getline(p_fin, line);
    // if (line != "Sale_ID, Date, Total_Price, Quantity_of_Items, Buyer, Seller") {
    //     std::cout << "Unable to load Parent Sales file. New one created.\n";
    //     return newFile();
    // };

    // while (!(p_fin.eof())) {
    //     getline(p_fin, line);
    //     //sscanf(line.c_str(), "%lu,%s,%lu,%lf,%lf,%s,%s", &id, &tp, &sp, &t, b, s);
    //     if (!loadTransaction(id, b, s, y, m, d)) {
    //         std::cerr << "FILE CURRUPTION DETECTED in File: " << parent_file << std::endl;
    //         return false;
    //     }
    // }
    // p_fin.close();
    return true;
}

bool SaleList::save() {
    std::ofstream p_fout, c_fout;
    //unsigned int i;

    p_fout.open(parent_file.c_str());
    if (!p_fout.is_open()) return false;

    // will have to redo this completely
    p_fout.close();
    return true;
}
