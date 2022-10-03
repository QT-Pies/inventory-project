#include "Date.hpp"

/*
 * Parses string and breaks it into integer portions; stores string
 */
Date::Date(const std::string& d)
{
    sscanf(d.c_str(), "%u/%u/%u", &month, &day, &year);
    string_date = d;
}