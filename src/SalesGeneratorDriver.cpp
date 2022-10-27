#include "SalesGenerator.hpp"

static void printUsage(std::ostream &out) {
    out << "usage: ./gen-inventory output_file.csv #undefined #non-perishable "
           "#perishable --flags"
        << std::endl;

    out << "usage: ./gen-sales inventory.csv MM/DD/YYYY #of transactions" << std::endl;
}

int main(int argc, char** argv) {

    /* Print usage if not correct amount of args. */
    if (argc != 4) {
        printUsage(std::cerr);
        return 1;
    }

    /* Otherwise, run the generator. */

    SalesGenerator generator(argv[1], argv[2]);

    generator.generateTransactions(std::stoul(argv[3]));

    return 0;
}