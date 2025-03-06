# include "BitcoinExchange.hpp"

Bitcoin::Bitcoin(){}

Bitcoin::Bitcoin(const Bitcoin &cpy) : data(cpy.data) {}

Bitcoin &Bitcoin::operator=(const Bitcoin &rhs)
{
	if (this != &rhs)
		data = rhs.data;
	return *this;
}

Bitcoin::~Bitcoin() {}

void Bitcoin::parse(Bitcoin &data, const char* file)
{
	(void)data;
	std::fstream fs;
	std::string line;

	fs.open(file, std::fstream::in); //fstream::in es un modo que solo le indica que leera ese archivo(tambien esta out que le servira para escribir)

	if (!fs.is_open())
	{
		throw std::logic_error("Failed to open input text");
	}
	while (std::getline(fs, line))
		std::cout << line << std::endl;
	fs.close();
	
}

void Bitcoin::found_file(Bitcoin &data)
{
	(void)data;
	std::string line;
	std::ifstream myFile ("./data.csv");

	if (!myFile.is_open())
	{
		throw std::logic_error("Failed to open dataBase(DB)");
	}
	while (std::getline(myFile, line))
		std::cout << line << std::endl;
	myFile.close();
} 
