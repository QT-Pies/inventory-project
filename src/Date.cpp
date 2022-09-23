#include "Date.hpp"

Date::Date(const std::string& d)
{
    sscanf(d.c_str(), "%u/%u/%u", month, day, year);
}

std::string Date::toString()
{
    stringstream ss;
    ss << month << '/' << day << '/' << year << std::endl;
    return ss.str();
}