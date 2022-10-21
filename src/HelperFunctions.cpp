#include "HelperFunctions.hpp"

unsigned long toUnsignedLong(const std::string& str) {
    /* Check if number is negative */
    if (str.front() == '-') {
        throw std::bad_argument("toUnsignedLong -- Expected number >= 0.");
    }

    /* Otherwise, it's >= 0, return it. */
    return std::stoul(str);
}

double toFauxUnsignedDouble(const std::string& str) {
    /* Check if number is negative */
    if (str.front() == '-') {
        throw std::bad_argument("toFauxUnsignedDouble -- Expected number >= 0.");
    }

    /* Otherwise, it's >= 0, return it. */
    return std::stod(str);
}