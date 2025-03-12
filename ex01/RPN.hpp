# pragma once
# include <iostream>
# include <string>
# include <stack>
# include <cstdlib>
# include <sstream>

# define CYAN "\033[96m"
# define YELLOW "\033[93m"
# define GREEN "\033[92m"
# define RED "\033[91m"
# define END_COLOR "\033[0m"

class RPN
{
	private:
		long double			_result;
		std::stack<float>	stack; // stack para almacenar los operandos mientras procesamos la expresion
	public:
		RPN();
		RPN(const RPN &cpy);
		RPN &operator=(const RPN &rhs);
		~RPN();
		bool parse(const char *argv);
		bool isDigitStr(const std::string &str);
		void putNumberOnStack(const std::string &str);
		bool operations(const std::string &str);
		void printResult(const char* operations) const;
};
