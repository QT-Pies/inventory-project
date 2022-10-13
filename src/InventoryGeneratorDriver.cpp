#include <iostream>
#include <string>

#include "InventoryGenerator.hpp"

static void printUsage(std::ostream& out) {
  out << "usage: ./gen-inventory output_file.csv #undefined #non-perishable "
         "#perishable --flags"
      << std::endl;
}

int main(int argc, char** argv) {
  InventoryGenerator gen;
  std::string help_arg;
  std::string argument;
  bool bad_found;
  int i;
  int input;

  help_arg = "";
  if (argc == 2) {
    help_arg = argv[1];
  }

  if ((help_arg == "--help" || help_arg == "-h")) {
    std::cout << "inventory-generator" << std::endl;
    printUsage(std::cout);
    std::cout << std::endl;

    std::cout << "\t--help / -h" << std::endl;
    std::cout << "\t\tPrints out the help message you are viewing now"
              << std::endl;
    std::cout << std::endl;

    std::cout << "\t--bad" << std::endl;
    std::cout << "\t\tPrecedes a list of keys that you want to generate bad "
                 "values for"
              << std::endl;
    std::cout << std::endl;

    std::cout << "\t--random" << std::endl;
    std::cout << "\t\tWhen used with --bad, each specified bad key has 1 / "
                 "bad_keys.size() chance of being a bad value"
              << std::endl;
    std::cout << "\t\tWhen used without --bad, each alternative row will "
                 "generate bad values"
              << std::endl;
    std::cout << std::endl;

    std::cout << "\t--random_factor" << std::endl;
    std::cout << "\t\tUsed with --random; larger numbers DECREASE the chance, "
                 "while a value of 0 guarantees it happening."
              << std::endl;
    std::cout << "\t\tIf flag is not given, defaults to 2" << std::endl;

    return 0;
  }

  if (argc < 5) {
    printUsage(std::cerr);
    exit(1);
  }

  bad_found = false;

  /* Traverse arguments passed in */
  for (i = 5; i < argc; ++i) {
    argument = argv[i];
    if (argument == "--bad")
      bad_found = true;
    else if (argument == "--random")
      gen.toggleRandom();
    else if (argument == "--random_factor") {
      /* Exit if no parameter */
      if ((i + 1) >= argc) {
        std::cerr << "Missing number after --random_factor" << std::endl;
        return -1;
      }

      argument = argv[i + 1];

      try {
        input = std::stoi(argument);
        gen.setRandomFactor(input);
      } catch (std::invalid_argument const& ex) {
        std::cerr
            << "Invalid argument.  A number should follow --random_factor."
            << std::endl;
        return -1;
      }

      ++i;
    } else if (bad_found)
      gen.setBadKey(argument);
  }

  gen.generateFile(argv[1], std::stoi(argv[2]), std::stoi(argv[3]),
                   std::stoi(argv[4]));
  //    gen.generateFile("test.csv", 3, 3, 4);

  return 0;
}
