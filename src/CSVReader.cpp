#include <string>
#include <iostream>
#include <fstream>

#include "CSVReader.hpp"

int main(void)
{

	std::string name, str_id, cat, sub_cat, str_qty, str_sale_price;
	std::string str_tax, str_total_price, str_buy_cost, str_profit, exp; 
	
	unsigned long qty, id;
	double sale_price, tax, total_price, buy_cost, profit;
	
	//obviously this can be changed to read a file from input or cmd line
	std::ifstream csv_file("CSVInput/big_file.csv");

	if(!csv_file.is_open()) std::cout << "ERROR: File Open" << '\n';
	
	while(csv_file.good()){

		getline(csv_file, name, ',');
		
		getline(csv_file, str_id, ',');
		id = stoul(str_id);
		
		getline(csv_file, cat, ',');
		
		getline(csv_file, sub_cat, ',');
		
		getline(csv_file, str_qty, ',');
		qty = stoul(str_qty);
		
		getline(csv_file, str_sale_price, ',');
		sale_price = stod(str_sale_price);

		getline(csv_file, str_tax, ',');
		tax = stod(str_tax);

		getline(csv_file, str_total_price, ',');
		total_price = stod(str_total_price);
		
		getline(csv_file, str_buy_cost, ',');
		buy_cost = stod(str_buy_cost);

		getline(csv_file, str_profit, ',');
		profit = stod(str_profit);

		getline(csv_file, exp, '\n');
		
		/*
		std::cout << "name " << name << '\n';
		std::cout << "id " << id << '\n';
		std::cout << "cat " <<category << '\n';
		std::cout << sub_cat << '\n';
		std::cout << quant << '\n';
		std::cout << sale_price << '\n';
		std::cout << tax << '\n';
		std::cout << total_price << '\n';
		std::cout << buy_cost << '\n';
		std::cout << profit << '\n';
		std::cout << expiry << '\n';

		if(category == "Perishable"){
			//use p_item = p ctor
		}
		else {
			//use non_p_item = non_p ctor
		}
		//alright dinner time then bedtime
		*/
	}

return 0;
}
