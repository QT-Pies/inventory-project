#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <iostream>

class Item
{
public:
    /*
     * Constructs an item with the given values.
     * @param string Name of item
     * @param string Category of item (Perishable | NonPerishable)
     * @param unsigned-long Quantity of item
     * @param unsigned-long ID of item
     * @param double Price of item
     * @param double Cost for store to purchase item
     * @param double Tax on item
    */ 
    Item(const std::string&, const std::string&, unsigned long, unsigned long, double, double, double);

    /* Destructor; does nothing */
    virtual ~Item() = default;

    /* Virtual print method; inherited classes implement this */
    virtual void print() = 0;
private:
    friend class ActiveInventory;
protected:
    std::string name;
    std::string category;
    std::string sub_category;
    unsigned long quantity;
    unsigned long id;
    double sale_price;
    double buy_cost;
    double tax;
    double total_price;
    double profit;
};

#endif