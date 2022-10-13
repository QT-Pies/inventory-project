#include "CSVEntry.hpp"

CSVEntry::CSVEntry() {}

void CSVEntry::printEntry(std::ostream& out) {
  out << name << ',';
  out << id << ',';
  out << category << ',';
  out << sub_category << ',';
  out << quantity << ',';
  out << sale_price << ',';
  out << tax << ',';
  out << total_price << ',';
  out << buy_cost << ',';
  out << profit << ',';
  out << expiration_date << std::endl;
}