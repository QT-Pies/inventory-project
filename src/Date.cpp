#include "Date.hpp"

Date::Date(const std::string &d) {
    int rv = sscanf(d.c_str(), "%u/%u/%u", &month, &day, &year);

    if (rv != 3) {
        throw std::invalid_argument("Bad date -- give in form of month/day/year.");
    }

    string_date = d;
}