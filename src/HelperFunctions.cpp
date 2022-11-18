#include "HelperFunctions.hpp"

unsigned long toUnsignedLong(const std::string& str) {
    /* Check if number is negative */
    if (str.front() == '-') {
        throw std::invalid_argument("toUnsignedLong -- Expected number >= 0.");
    }

    /* Otherwise, it's >= 0, return it. */
    return std::stoul(str);
}

double toFauxUnsignedDouble(const std::string& str) {
    /* Check if number is negative */
    if (str.front() == '-') {
        throw std::invalid_argument("toFauxUnsignedDouble -- Expected number >= 0.");
    }

    /* Otherwise, it's >= 0, return it. */
    return std::stod(str);
}

void lowerCaseString(std::string& str) {
    /* Traverse string */
    for (char& c : str) {
        /* If char is an alphabetical char, lowercase it. */
        if (isalpha(c)) {
            c = tolower(c);
        }
    }
}