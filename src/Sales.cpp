#include "Sales.hpp"

/*
 * Constructor for base Sales class, initializes data to given values.
 */
Sale::Sale(const unsigned int id, const unsigned int sn, const std::string& d, const unsigned int as, const double sp, const double t, const std::string& b, const std::string& s)
: identification(id), sale_number(sn), date(d), amount_sold(as), sale_price(sp), tax(t), buyer(b), seller(s)
{
    total_price = sale_price + (tax * sale_price);
}

Sale::~Sale()
{
    /*
     * Shared pointers are used, so pointers will free themselves.
     */
}

/*
 * Initilizes what file will be used to load/save the sales data to.
 */
SaleList::SaleList(const std::string& f)
{
    file_name = f;
    offset = 0;
}

/*
 * Creates a new sale to put in the sales vector.
 * May change to throwing an exeption in the future.
 * Also may change error checking here based on Sales date restrictions.
 */
bool SaleList::addSale(const unsigned int id, const unsigned int sn, const std::string& d, const unsigned int as, const double sp, const double t, const std::string& b, const std::string& s)
{
    if(id == 0 || sn == 0 || as == 0 || sp == 0 || d == "" || b == "") 
    {
        std::cerr << "Failed to read Sales Input. Note that the ID, Sales Number, and Sales Price cannot be 0 and a Date and Buyer must be given.\nContinuing to read.";
        return false;
    }

    auto new_sale = std::make_shared<Sale>(id, sn, d, as, sp, t, b, s);
    sales.push_back(new_sale);
    return true;
}

/*
 * Creates a new file with the propper starting format.
 */
bool SaleList::newFile()
{
    std::ofstream fout;

    fout.open(file_name.c_str());
    if(!fout.is_open()) return false;

    fout << "ID,Sale Number,Date,Amount Sold,Sale Price,Tax,Buyer,Seller";
    fout.close();
    return true;
}

/* 
 * Reads in information from given file and holds it in the sales vector
 * If addSale returns false, then an error occured and false is returned.
 */
bool SaleList::load()
{
    std::ifstream fin;
    std::string line;

    unsigned int id;
    unsigned int sn;
    char d[20];
    unsigned int as;
    double sp;
    double t;
    char b[50];
    char s[50];

    fin.open(file_name.c_str());
    if(!fin.is_open()) return false;

    std::getline(fin, line);
    if(line != "ID,Sale Number,Date,Amount Sold,Sale Price,Tax,Buyer,Seller") return false;

    while(!(fin.eof()))
    {
        std::getline(fin, line);
        sscanf(line.c_str(),"%u,%u,%s,%u,%lf,%lf,%s,%s", &id, &sn, d, &as, &sp, &t, b, s);
        if(!addSale(id, sn, d, as, sp, t, b, s))
        {
            std::cerr << "FILE CURRUPTION DETECTED in File: " << file_name << std::endl;
            return false;
        }
        offset++;
    }
    fin.close();
    return true;
}

/*
 * Saves the sales information from the vector to the given file, uses append and the offset value 
 * so only newly added information will be saved.
 */
bool SaleList::save()
{
    std::ofstream fout;
    unsigned int i;

    fout.open(file_name.c_str(), std::ios::app);
    if(!fout.is_open()) return false;

    for(i = offset; i < sales.size(); i++)
    {
        fout << std::endl << sales[i]->identification << "," << sales[i]->sale_number << "," << sales[i]->date << "," << sales[i]->amount_sold << "," << sales[i]->sale_price << "," << sales[i]->tax << "," << sales[i]->buyer << "," << sales[i]->seller;
    }
    fout.close();
    return true;
}