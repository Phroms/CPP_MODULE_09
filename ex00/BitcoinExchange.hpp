# pragma once
# include <iostream>
# include <fstream>
# include <map>
# include <string>

template <typename T>
class Bitcoin
{
	private:
		std::map<std::string, unsigned int> _num; // un map para almacenar las fechas y horas

	public:
	void read_file();
};

