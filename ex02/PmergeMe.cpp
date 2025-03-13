# include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

void PmergeMe::printVect(const std::vector<int> &vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << YELLOW << "Print Vector: " << END_COLOR << vec[i];
		std::cout << std::endl;

	}
}

void PmergeMe::printDeqe(const std::deque<int> &deq)
{
	for (size_t i = 0; i < deq.size(); i++)
	{
		std::cout << YELLOW << "Print Deque: " << END_COLOR << deq[i];
		std::cout << std::endl;
	}
}
