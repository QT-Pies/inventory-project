#ifndef DATE_HPP
#define DATE_HPP

#include <cstdio>
#include <sstream>
#include <string>

class Date {
   public:
    /*
     * Constructor; takes std::string, stores it into class data.
     * @param string Expiration date in string format
     */
    Date(const std::string&);

    /* I opted to make these members public, as I think it makes sense in a non-important class like this. */
    std::string string_date;
    unsigned int year;
    unsigned int month;
    unsigned int day;

   private:
    friend class ActiveInventory;
};

#endif