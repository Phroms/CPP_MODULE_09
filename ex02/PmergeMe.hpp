# pragma once
# include <iostream>
# include <vector>
# include <deque>
# include <algorithm>
# include <ctime>
# include <sstream>

# define CYAN "\033[96m"
# define GREEN "\033[92m"
# define BLUE "\033[94m"
# define YELLOW "\033[93m"
# define RED "\033[91m"
# define END_COLOR "\033[0m"

typedef clock_t aaaa;

class PmergeMe
{
	private:	
		std::vector<int> _vec;
		std::deque<int> _deq; // Mas eficiente en inserciones y eliminacion al principio y al final, util para probar rendimiento contra vector.
	public:
		PmergeMe();
		~PmergeMe();
		void sortVector(std::vector<int> &vec);
		void sortDeque(std::deque<int> &deq);
		void printAfter(const std::vector<int> &vec);
		void printBefore(const std::vector<int> &vec);

		void calculateTime(std::vector<int> &vec, std::deque<int> &deq);
};
