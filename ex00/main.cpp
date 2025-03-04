# include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	(void)argv;
	if (argc < 2)
	{
		std::cerr << "No se pudo abrir el archivo" << std::endl;
		return 1;
	}
	if (std::string (argv[1]) != "input.txt")
	{
		std::cerr << "Error: Solo se puede leer el archivo especificado" << std::endl;
		return 1;
	}
	read_file();
}
