# include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << RED << "ERROR: " << END_COLOR << "There are not enough arguments" << std::endl;
		return 1;
	}
	RPN operations;

	if (!operations.parse(argv[1]))
		return 1;
	operations.printResult(argv[1]);
	return 0;
}
