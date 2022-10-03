#include "CSVEntry.hpp"

/*
 * Empty constructor; the compiler wanted this for some reason.
 */
CSVEntry::CSVEntry()
{
}

/*
 * Print out the entry to given ostream.
 */
void CSVEntry::printEntry(std::ostream& out)
{
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