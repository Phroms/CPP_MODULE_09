# include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		throw std::logic_error("There is only one argument");
		return 1;
	}

	try
	{
		Bitcoin data;

		data.found_file(data);
		data.parse(data, argv[1]);;
	}
	catch(const std::exception &e)
	{
		std::cerr << RED << "ERROR" << END_COLOR << e.what() << std::endl;
		return 1;
	}
	return 0;
}
