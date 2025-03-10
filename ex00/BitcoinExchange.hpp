# pragma once
# include <iostream>
# include <fstream>
# include <sstream>
# include <stdexcept>
# include <algorithm>
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
		float getRate(const std::string &date) const;
		bool found_file(const char* file);
		void parse(Bitcoin &data, const char* file);
		bool found_date(const std::string &date);
};
