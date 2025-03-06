# pragma once
# include <iostream>
# include <fstream>
# include <stdexcept>
# include <map>
# include <string>

# define CYAN "\033[96m"
# define RED "\033[91m"
# define END_COLOR "\033[0m"

class Bitcoin
{
	typedef	std::map<std::string, float> map; // un map para almacenar las fechas y horas
	private:
		map data;
	public:
		Bitcoin();
		Bitcoin(const Bitcoin &cpy);
		Bitcoin &operator=(const Bitcoin &rhs);
		~Bitcoin();
		void parse(Bitcoin &data, const char* file);
		void found_file(Bitcoin &data);
};
