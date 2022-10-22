#ifndef HELPER_FUNCTIONS_HPP
#define HELPER_FUNCTIONS_HPP

#include <string>
#include <stdexcept>

/*
 * @brief Attempts to convert a string to an unsigned long, and errors if it's negative.
 * @param std::string The number in string format.
 * @return Number if string is non-negative, bad_argument exception is thrown otherwise.
*/
unsigned long toUnsignedLong(const std::string&);

/*
 * @brief Attempts to convert a string to a double, but throws an error if it's negative.
 * We don't want some of our doubles to be < 0, but there is no "unsigned double" data type, hence the "fauxUnsignedDouble" to clarify that.
 * @param std::string The number in string format.
 * @return Number if string is non-negative, bad_argument exception is thrown otherwise.
*/
double toFauxUnsignedDouble(const std::string&);

/*
 * @brief Converts a string to the lowercase equivalent.
 * @param std::string String to lowercase.
 * @return Nothing -- takes reference.
*/
void lowerCaseString(std::string&);
#endif