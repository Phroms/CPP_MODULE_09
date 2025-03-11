# include "BitcoinExchange.hpp"

bool OpenFile(const char* file)
{
	if (!file)
	{
		return false;
	}

	std::ifstream inputFile(file);
	if (!inputFile.is_open())
	{
		return false;
	}

	inputFile.close();
	std::cout << YELLOW << "\nFile FOUND!!\n" << "\n" << CYAN << "Loading ....\n" << END_COLOR << std::endl;
	return true;
}

int main(int argc, char **argv)
{
	Bitcoin bitcoin;

	if (argc > 2)
	{
		std::cout << RED << "Error: " << END_COLOR << "2 arguments expected" << std::endl;
		return 1;
	}
	else if (!OpenFile(argv[1]))
	{
		std::cerr << RED << "Error: " << END_COLOR << "File not FOUND!!" << std::endl;
		return 1;
	}

	if (!bitcoin.found_file("data.csv"))
		return 1;
	bitcoin.parse(argv[1]);

	return 0;
}
