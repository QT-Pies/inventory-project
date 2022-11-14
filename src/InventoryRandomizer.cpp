#include "InventoryRandomizer.hpp"

Entry::Entry(std::string item, std::string cat, std::string sub_cat, std::string loc) {
    name = item;
    category = cat;
    sub_category = sub_cat;
    location = loc;
    quantity = 0;
    backorder = 0;
    id = 0;
    sale_price = 0;
    buy_cost = 0;
    tax = 0;
    total_price = 0;
    profit = 0;
    expiration_date = "-1";
}

void Entry::print() 
{
    std::cout << name << ",";
    std::cout << id << ",";
    std::cout << category << ",";
    std::cout << sub_category<< ",";
    std::cout << location << ",";
    std::cout << quantity << ",";
    std::cout << backorder << ",";
    std::cout << sale_price << ",";
    std::cout << tax << ",";
    std::cout << total_price << ",";
    std::cout << buy_cost << ",";
    std::cout << profit << ",";
    std::cout << expiration_date << std::endl;
}

InventoryRandomizer::InventoryRandomizer(std::string file, std::string out) 
{
    input_file = file;
    out_file = out;
    readFile();
    generateRandom();
    outputFile();
}

void InventoryRandomizer::readFile() 
{
    
    std::string item, cat, sub_cat, loc, tmp;
    std::ifstream f(input_file);

    getline(f, tmp, '\n');

    while(f.good()) {
        getline(f, item, ',');        
        getline(f, cat, ',');
        getline(f, sub_cat, ',');
        getline(f, loc, '\n');        

        std::shared_ptr<Entry> e = std::make_shared<Entry>(item,cat,sub_cat,loc);
        entries.push_back(e);
    }
}

void InventoryRandomizer::outputFile() 
{
    unsigned int i;
    
    for (i = 0; i < entries.size(); i++) {
        entries[i]->print();
    }

}

void InventoryRandomizer::generateRandom()
{

    unsigned int i;
    
    std::default_random_engine generator;
    std::normal_distribution<double> sell_price(5.5,.1);
    std::normal_distribution<double> buy_price(2.0, .5);
    std::normal_distribution<double> tax(.05, .002);
    std::normal_distribution<double> quant(1000.0,10.0);
    std::normal_distribution<double> back(200.0,10.0);

    for (i = 0; i < entries.size(); i++) {
        entries[i]->id = (int)i;
        entries[i]->quantity = (int)quant(generator);
        entries[i]->backorder = (int)back(generator);
        entries[i]->buy_cost = buy_price(generator);
        entries[i]->sale_price = sell_price(generator);
        entries[i]->tax = tax(generator);
        entries[i]->total_price = (entries[i]->tax * entries[i]->sale_price) + entries[i]->sale_price;
        entries[i]->expiration_date = "-1";
        entries[i]->profit = entries[i]->sale_price - entries[i]->buy_cost;
    }

}