# pragma once
# include <iostream>
# include <vector>
# include <deque>
# include <algorithm>

# define CYAN "\033[96m"
# define GREEN "\033[94m"
# define YELLOW "\033[93m"
# define RED "\033[91m"
# define END_COLOR "\033[0m"

class PmergeMe
{
	private:	
		std::vector<int> _vec;
		std::deque<int> _deq; // Mas eficiente en inserciones y eliminacion al principio y al final, util para probar rendimiento contra vector.
	public:
		PmergeMe();
		~PmergeMe();
		void sortVector(const std::vector<int> &vec);
		void sortDeque(const std::deque<int> &deq);
		void printVect(const std::vector<int> &vec);
		void printDeqe(const std::deque<int> &deq);
};
