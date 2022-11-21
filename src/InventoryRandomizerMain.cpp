#include <iostream>

#include "InventoryRandomizer.hpp"

int main(int argc, char** argv) {
    std::string in;
    std::string out;

    if (argc < 3) {
        fprintf(stderr, "Usage: bin/randomize-inventory input_file output_file\n");
        return -1;
    }

    in = argv[1];
    out = argv[2];
    InventoryRandomizer inv_ran(in, out);

    return 0;
}