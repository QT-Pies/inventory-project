#include <fstream>
#include <iostream>
#include "Sales.hpp"

// need to do correct line spacing
/*
 * Constructor for base Sales class; initializes data to given values.
 */
Sale::Sale(Item* i, const unsigned int sn, const std::string& d, const unsinged int as, const std::string& b, const std::string& s)
: item(i), sale_number(sn), amount_sold(as), buyer(b), seller(s)
{
    date(d);
}




SaleList::SaleList()
{
    if(load()) cout << "Sales Loaded\n";
    else cout << "Unable to Load Sales\n";
}

bool SaleList::load()
{
    return false;
}

bool SaleList::save()
{
    std::ofstream fout;
    int i;
    sale sit;

    fout.open("Sales.csv");

    if(fout.fail()) return false;

    // possibly could switch up implimintation
    for(i = 0; i < sales.size(); i++){
        fout << sit->item-> << "," << it->sale_number << "," << date.string_date.c_str() << "," << amount_sold << "," << buyer << "," << seller << endl;
    }
}