#ifndef DATE_HPP
#define DATE_HPP

#include <cstdio>
#include <string>
#include <sstream>

class Date
{
public:
    /* Constructor; takes std::string, stores it into class data. */
    Date(const std::string&);

    /* I opted to make these members public, as I think it makes sense in a non-important class like this. */
    std::string string_date;
    unsigned int year;
    unsigned int month;
    unsigned int day;
};

#endif