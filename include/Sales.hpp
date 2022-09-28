// just trying to commit hopefull it doesnt get pushed

#ifndef SALES_HPP
#define SALES_HPP

#include <string>
#include <memory>
#include "Item.hpp"
#include "Date.hpp"


// have name of item, dont need to store any redundant information, only relivante data
// Sale Number, 

// may want to use the date class instead of string, just depends on when we want to do date conversion


class Sale
{
friend class SaleList;
public:
    Sale(Item*, const unsigned int, const std::string&, const unsinged int, const std::string&, const std::string&);
    virtual ~Sale() = default;
    virtual void print() = 0;
    // maybe change to a bool or something, in case it fails
    // add a vector or map to store all of the sales currently stored
    // write into a basic main file to test this
    // add a feture to read it in
protected:
    Item * item;
    unsigned int sale_number;
    Date date;
    unsigned_int amount_sold;
    std::string buyer;
    std::string seller;
};

class SaleList
{
public:
    SaleList();
    bool addSale(Item*, const unsigned int, const std::string&, const unsinged int, const std::string&, const std::string&)
    bool load();
    bool save();
private:
    vector<Sale> sales;
};

#endif