#include <fstream>
#include <iostream>
#include <stdio.h>
#include "Sales.hpp"

/*
 * Constructor for base Sales class, initializes data to given values.
 */
Sale::Sale(const unsigned int id, const unsigned int sn, const std::string& d, const unsigned int as, const double sp, const double t, const std::string& b, const std::string& s)
: identification(id), sale_number(sn), date(d), amount_sold(as), sale_price(sp), tax(t), buyer(b), seller(s)
{
    total_price = sale_price + (tax * sale_price);
}



/*
 * Initilizes what file will be used to load/save the sales data to.
 */
SaleList::SaleList(const std::string& f)
{
    file = f;
}

/*
 * Creates a new sale to put in the sales vector
 */
bool SaleList::add_sale(const unsigned int id, const unsigned int sn, const std::string& d, const unsigned int as, const double sp, const double t, const std::string& b, const std::string& s)
{
    if(id == 0 || sn == 0 || as == 0 || sp == 0) return false;
    Sale new_sale(id, sn, d, as, sp, t, b, s);
    salles.push_back(new_sale);
    return true;
}

/*
 * Creates a new file with the propper starting format.
 */
bool SaleList::new_file()
{
    std::ofstream fout;

    fout.open(file.c_str());
    if(!fout) return false;

    fout << "ID,Sale Number,Date,Amount Sold,Sale Price,Tax,Buyer,Seller";
    fout.close();
    return true;
}

/* 
 * Reads in information from given file and holds it in the sales vector
 */
bool SaleList::load()
{
    std::ifstream fin;
    int i;
    std::string line;

    unsigned int id;
    unsigned int sn;
    std::string d;
    unsigned int as;
    double sp;
    double t;
    std::string b;
    std::string s;

    fin.open(file.c_str());
    if(!fin) return false;

    std::getline(fin, line);
    if(line != "ID,Sale Number,Date,Amount Sold,Sale Price,Tax,Buyer,Seller") return false;
    line.clear();

    offset = 0;

    while(!(file.eof())){
        std::getline(fin, line);
        sscanf(line.c_str(),"%u,%u,%s,%u,%f,%f,%s,%s", id, sn, d, as, sp, t, b, s);
        add_sale(id, sn, d, as, sp, t, b, s);
        line.clear();
        offset++;
    }
    fin.close();
    return true;
}

/*
 * Saves the sales information from the vector to the given file
 */
bool SaleList::save()
{
    std::ofstream fout;
    int i;
    sale sit;

    fout.open("Sales.csv");
    if(fout.fail()) return false;

    fout << "ID,Sale Number,Date,Amount Sold,Sale Price,Tax,Buyer,Seller";

    // possibly could switch up implimintation
    for(i = 0; i < sales.size(); i++){
        sit = sales[i];
        fout << endl << sit->identification << "," << sit->sale_number << "," << sit->date << "," << sit->amount-sold << "," << sit->sales_price << "," << sit->tax  "," << buyer << "," << seller << endl;
    }
    fout.close();
    return true;
}

int main(){
    return 0;
}