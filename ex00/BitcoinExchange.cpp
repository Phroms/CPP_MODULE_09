# include "BitcoinExchange.hpp"
#include <fstream>
#include <ostream>

void read_file()
{
	std::ifstream myFile ("input.txt");

	if (!myFile.is_open())
	{
		std::cerr << "Error: archivo no abierto" << std::endl;
	}
} 
