#include <string>
#include <iostream>
#include <fstream>

/*making a little change on lne 5 :)*/

#include "CSVReader.hpp"

int main(void)
{

	std::string name, id, category, sub_cat, quant, sale_price;
	std::string tax, total_price, buy_cost, profit, expiry; 
	
	PerishableItem p_item;
	NonPerishableItem non_p_item;


	//obviously this can be changed to read a file from input or cmd line
	std::ifstream csv_file("CSVInput/big_file.csv");

	if(!csv_file.is_open()) std::cout << "ERROR: File Open" << '\n';

	else std::cout << "good job jen!\n";
	
	while(csv_file.good()){

		getline(csv_file, name, ',');
		getline(csv_file, id, ',');
		getline(csv_file, category, ',');
		getline(csv_file, sub_cat, ',');
		getline(csv_file, quant, ',');
		getline(csv_file, sale_price, ',');
		getline(csv_file, tax, ',');
		getline(csv_file, total_price, ',');
		getline(csv_file, buy_cost, ',');
		getline(csv_file, profit, ',');
		getline(csv_file, expiry, '\n');
		
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

	}

return 0;
}
