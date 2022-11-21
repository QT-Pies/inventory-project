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

void Entry::print(std::ofstream &of) 
{
    /*outputs to given file stream*/
    of << name << ",";
    of << id << ",";
    of << category << ",";
    of << sub_category<< ",";
    of << location << ",";
    of << quantity << ",";
    of << backorder << ",";
    of << std::setprecision(2) << std::fixed << std::showpoint << sale_price << ",";
    of << tax << ",";
    of << total_price << ",";
    of << buy_cost << ",";
    of << profit << ",";
    of << expiration_date << std::endl;
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

    while(f.peek() != EOF) {
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
    std::ofstream of(out_file);

    of << "Name,ID,Category,Sub-Category,Location,Quantity,Backorder,Sale Price,Tax,Total Price,Buy Cost,Profit,Expiration Date" << std::endl;
    
    for (i = 0; i < entries.size(); i++) {
        entries[i]->print(of);
    }

    of.close();
}

void InventoryRandomizer::generateRandom()
{
    std::stringstream ss;
    unsigned int i, seed;
    
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> sell_price(5.5,.1);
    std::normal_distribution<double> buy_price(2.0, .5);
    std::normal_distribution<double> tax(.05, .01);
    std::normal_distribution<double> quant(1000.0,10.0);
    std::normal_distribution<double> back(200.0,10.0);
    std::uniform_int_distribution<int> month(1, 12);
    std::uniform_int_distribution<int> day(1,28);        
    std::uniform_int_distribution<int> year(2023, 2028);  

    for (i = 0; i < entries.size(); i++) {
        entries[i]->id = (int)i;
        entries[i]->quantity = (int)quant(generator);
        entries[i]->backorder = (int)back(generator);
        entries[i]->buy_cost = buy_price(generator);
        entries[i]->sale_price = sell_price(generator);
        entries[i]->tax = tax(generator);
        entries[i]->total_price = (entries[i]->tax * entries[i]->sale_price) + entries[i]->sale_price;
        entries[i]->profit = entries[i]->sale_price - entries[i]->buy_cost;

        if (entries[i]->category == "Perishable") {
            ss.str("");
            ss.clear();
            ss << month(generator) << "/" << day(generator) << "/" << year(generator);
            entries[i]->expiration_date = ss.str();
        }
    }

}