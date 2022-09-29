#include <iostream>
#include <string>
#include "CSVGenerator.hpp"

static void print_usage(std::ostream& out)
{
    out << "usage: ./gen-csv output_file.csv #undefined #non-perishable #perishable --flags" << std::endl;
}

int main(int argc, char** argv)
{
    CSVGenerator gen;
    std::string help_arg;
    std::string argument;
    bool bad_found;
    int i;

    help_arg = argv[1];

    if (argc == 2 && (help_arg == "--help" || help_arg == "-h"))
    {
        std::cout << "inventory-generator" << std::endl;
        print_usage(std::cout);
        std::cout << std::endl;

        std::cout << "\t--help / -h" << std::endl;
        std::cout << "\t\tPrints out the help message you are viewing now" << std::endl;
        std::cout << std::endl;

        std::cout << "\t--bad" << std::endl;
        std::cout << "\t\tPrecedes a list of keys that you want to generate bad values for" << std::endl;

        return 0;
    }

    if (argc < 5)
    {
        print_usage(std::cerr);
        exit(1);
    }

    bad_found = false;

    /* Traverse arguments passed in */
    for (i = 5; i < argc; ++i)
    {
        argument = argv[i];
        if (argument == "--bad") bad_found = true;
        else if (bad_found) gen.setBadKey(argument);
    }

    gen.generateFile(argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]));
//    gen.generateFile("test.csv", 3, 3, 4);

    return 0;
}