#include "NonPerishableItem.hpp"

NonPerishableItem::NonPerishableItem(const std::string& nm,
                                     const std::string& cat,
                                     const std::string& sub_cat,
                                     unsigned long qty, unsigned long idd,
                                     double price, double cost, double tx)
    : Item(nm, cat, sub_cat, qty, idd, price, cost, tx) {}

void NonPerishableItem::print() {
  std::cout << "ID: " << id << " Item: " << name << std::endl;
  std::cout << "In-Stock: " << quantity << std::endl;
  std::cout << "Stocking/Purchase Cost: " << buy_cost << std::endl;
  std::cout << "Sale Price: " << sale_price << std::endl;
  std::cout << "Tax on Item: " << tax * sale_price << std::endl;
  std::cout << "Profit per unit sold: " << profit << std::endl;
}

void NonPerishableItem::printCSV(std::ofstream& file) {
  file << name << ",";
  file << id << ",";
  file << category << ",";
  file << sub_category << ",";
  file << quantity << ",";
  file << sale_price << ",";
  file << tax << ",";
  file << total_price << ",";
  file << buy_cost << ",";
  file << profit << ",";
  file << "-1";
}

NonPerishableItem::~NonPerishableItem() {}
