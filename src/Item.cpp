#include "Item.hpp"

Item::Item(const std::string& nm, const std::string& cat,
           const std::string& sub_cat, unsigned long qty, unsigned long idd,
           double price, double cost, double tx)
    : name(nm),
      category(cat),
      sub_category(sub_cat),
      quantity(qty),
      id(idd),
      sale_price(price),
      buy_cost(cost),
      tax(tx) {
  profit = sale_price - buy_cost;
  total_price = sale_price + (tax * sale_price);
}
