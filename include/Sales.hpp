// just trying to commit hopefull it doesnt get pushed

#ifndef SALES_HPP
#define SALES_HPP

#include <string>
#include <fstream>
#include "Item.hpp"

class Sale
{
friend class SaleList;
public:
    Sale(const unsigned int, const unsigned int, const std::string&, const unsigned int, const double, const double, const std::string&, const std::string&);
protected:
    unsigned int id;
    unsigned int sale_number;
    std::string date;
    unsigned int amount_sold;
    double sale_price;
    double tax;
    double total_price;
    std::string buyer;
    std::string seller;
};

class SaleList
{
public:
SaleList(const std::string&)
    bool add_sale(const unsigned int, const unsigned int, const std::string&, const unsigned int, const double, const double, const std::string&, const std::string&)
    bool new_file();
    bool load();
    bool save();
protected:
    std::vector<Sale> sales;
    std::string file;
};

#endif