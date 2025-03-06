# include "BitcoinExchange.hpp"

void read_file(char **argv)
{
	std::string line;

	std::ifstream myFile (argv[1]);

	if (!myFile)
	{
		std::cerr << "Error: al intentar abrir el archivo" << std::endl;
		return;
	}

	while (std::getline(myFile, line))
		std::cout << line << std::endl;
	myFile.close();
} 
