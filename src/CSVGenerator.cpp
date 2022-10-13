#include "CSVGenerator.hpp"

CSVGenerator::CSVGenerator() { id_count = 0; }

/*
 * Generates a file named by the file_name param. with entries number of items.
 */
void CSVGenerator::generateFile(const std::string& file_name,
                                unsigned int unknown,
                                unsigned int non_perishable,
                                unsigned int perishable) {
  unsigned int i;

  /* Attempt to open file and throw exception if failed */
  file.open(file_name);
  if (!file.is_open()) throw std::string("Failed to open file for writing.");

  for (size_t j = 0; j < columns.size(); ++j) {
    file << columns[j];
    if (j != columns.size() - 1) file << ',';
  }
  file << std::endl;

  for (i = 0; i < unknown; ++i) {
    auto entry = generateItem();
    entry->printEntry(file);
  }

  for (i = 0; i < non_perishable; ++i) {
    auto entry = generateNonPerishableItem();
    entry->printEntry(file);
  }

  for (i = 0; i < perishable; ++i) {
    auto entry = generatePerishableItem();
    entry->printEntry(file);
  }

  file.close();
}

std::shared_ptr<CSVEntry> CSVGenerator::generateItem() {
  std::random_device rand;
  std::mt19937 gen(rand());
  std::uniform_int_distribution<int> distrib_size(1, 32);
  std::uniform_int_distribution<int> distrib_index(0, 51);
  std::uniform_int_distribution<int> distrib_int(0, 1000);
  std::uniform_real_distribution<double> distrib_double(0.25, 10000);
  std::shared_ptr<CSVEntry> entry;

  entry = std::make_shared<CSVEntry>();

  /* Generate a random length string and push back that many random chars */
  int name_length = distrib_size(gen);
  for (int i = 0; i < name_length; ++i) {
    entry->name.push_back(chars[distrib_index(gen)]);
  }

  /* Set category to undefined, it's not perishable or non-perishable. */
  entry->category = "-1";
  entry->sub_category = "-1";
  entry->expiration_date = "-1";

  entry->quantity = distrib_int(gen);

  entry->id = id_count;
  id_count++;

  entry->sale_price = distrib_double(gen);

  std::uniform_real_distribution<double> distrib_cost(0.05,
                                                      entry->sale_price / 2);
  entry->buy_cost = distrib_cost(gen);

  entry->tax = 0.1;
  entry->total_price = entry->tax + entry->sale_price;
  entry->profit = entry->sale_price - entry->buy_cost;

  return entry;
}

/*
 * Generate a non-perishable Item.
 */
std::shared_ptr<CSVEntry> CSVGenerator::generateNonPerishableItem() {
  auto entry = generateItem();
  entry->category = "NonPerishable";
  return entry;
}

/*
 * Generate a perishable item.
 */
std::shared_ptr<CSVEntry> CSVGenerator::generatePerishableItem() {
  std::random_device rand;
  std::mt19937 gen(rand());
  std::uniform_int_distribution<int> distrib_month(1, 12);
  std::uniform_int_distribution<int> distrib_day(
      1, 28);  // let's pretend all months have 28
  std::uniform_int_distribution<int> distrib_year(
      2023, 2035);  // years chosen for no reason
  std::stringstream ss;

  ss << distrib_month(gen) << '/' << distrib_day(gen) << '/'
     << distrib_year(gen);

  auto entry = generateItem();
  entry->category = "Perishable";
  entry->expiration_date = ss.str();

  return entry;
}
