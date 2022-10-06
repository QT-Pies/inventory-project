#include "Date.hpp"

Date::Date(const std::string& d) {
    sscanf(d.c_str(), "%u/%u/%u", &month, &day, &year);
    string_date = d;
}