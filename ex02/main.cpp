# include "PmergeMe.hpp"
#include <sstream>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << RED << "Error: There are not enough arguments" << END_COLOR << std::endl;
		return 1;
	}
	std::vector<int> vector;
	std::deque<int> deque;

	for (int i = 1; i < argc; i++) // Comienza en 1 porque si empieza en 0 se encuentra el primer argumento que es el nombre del programa(./PmergeMe)
	{
		std::istringstream iss(argv[i]);
		int num;

		if (!(iss >> num) || num <= 0)
		{
			std::cerr << RED << "ERROR: Invalid number => " << END_COLOR << argv[i] << std::endl;
			return 1;
		}

		vector.push_back(num);
		deque.push_back(num);
	}

	PmergeMe pmerge;

	pmerge.printVect(vector);
	pmerge.printDeqe(deque);

	pmerge.sortVector(vector);
	pmerge.sortDeque(deque);

	return 0;
}
