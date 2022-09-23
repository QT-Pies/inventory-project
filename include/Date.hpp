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

    /* Converts the stored data to a string for easy printing */
    std::string toString();

    /* I opted to make these members public, as I think it makes sense in a non-important class like this. */
    unsigned int year;
    unsigned int month;
    unsigned int day;
};

#endif