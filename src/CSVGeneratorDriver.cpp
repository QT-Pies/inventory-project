#include <iostream>
#include <string>
#include "CSVGenerator.hpp"

int main(int argc, char** argv)
{
    CSVGenerator gen;

    if (argc != 5)
    {
        std::cerr << "usage: ./gen-csv output_file.csv #undefined items #non-perishable items #perishable items" << std::endl;
        return -1;
    }

    gen.generateFile(argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]));
//    gen.generateFile("test.csv", 3, 3, 4);

    return 0;
}