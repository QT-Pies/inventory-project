#include <string>
#include <iostream>
#include <fstream>

#include "CSVReader.hpp"

int main(void)
{

	std::string name;

	std::ifstream csv_file("CSVInput/big_file.csv");

	if(!csv_file.is_open()) std::cout << "ERROR: File Open" << '\n';

	else std::cout << "good job jen!\n";
	
	while(csv_file.good()){

		getline(csv_file, name, ',');
		
		std::cout << "file name: " << name << '\n';
	}

return 0;
}
