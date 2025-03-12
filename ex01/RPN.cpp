# include "RPN.hpp"

RPN::RPN()
{
	_result = 0;
}

RPN::RPN(const RPN &cpy)
{
	*this = cpy;
}

RPN &RPN::operator=(const RPN &rhs)
{
	if (this != &rhs)
	{
		stack = rhs.stack;
	}
	return *this;
}

RPN::~RPN()
{
}

bool RPN::parse(const char *argv)
{
	if (!argv || argv == NULL)
	{
		std::cout << RED << "ERROR: " << END_COLOR << "The argv is empty" << std::endl;
		return false;
	}

	std::stringstream str(argv); // guardamos todo el contenido en str
	std::string token;

	while (std::getline(str, token, ' ')) // guardamos todo lo leido en token
	{
		if (isDigitStr(token))
		{
			putNumberOnStack(token);
		}
		else if (stack.size() >= 2)
		{
			if (!operations(token))
				return false;
		}
		else
		{
			std::cout << RED << "ERROR: " << END_COLOR << "Only numbers and operations is accepted" << std::endl;
			return false;
		}
	}
	// Comprueba si solo hay un elemento en la pila=stack
	if (stack.size() != 1)
	{
		std::cout << RED << "ERROR: Invalid Input." << std::endl;
		return false;
	}
	return true;
}

// Si al terminar, da error, revisar este metodo junto al de abajo
bool RPN::isDigitStr(const std::string &str)
{
	return (str.find_first_not_of("0123456789") == std::string::npos);
}

// 
void RPN::putNumberOnStack(const std::string &str)
{
	stack.push(std::atof(str.c_str()));
}

bool RPN::operations(const std::string &str)
{
	// porque primero stack2 y despues stack1, es para stack2 obtiene el ultimo de la pila
	// y el stack1 obitene el siguiente que estaba abajo de la pila
	// es mas que todo para tener el orden en los numeros
	// ejemplo: 80 20 40 -> 20 40 80
	float stack2 = stack.top(); // .top obtiene el elemento de la cima de la pila
	stack.pop(); // .pop elimina el elemento superior de la pila
	
	float stack1 = stack.top();
	stack.pop();

	float result;

	if (str == "+")
	{
		result = stack1 + stack2;
		std::cout << YELLOW << "SUMA: \t" << END_COLOR << stack1 << "+" << stack2 << "=" << result << std::endl;
	}
	else if (str == "-")
	{
		result = stack1 - stack2;
		std::cout << YELLOW << "RESTA: \t" << END_COLOR << stack1 << "-" << stack2 << "=" << result << std::endl;
	}
	else if (str == "*")
	{
		result = stack1 * stack2;
		std::cout << YELLOW << "MULTI: \t" << END_COLOR << stack1 << "*" << stack2 << "=" << result << std::endl;
	}
	else if (str == "/")
	{
		if (stack2 == 0) // Un if para ver que no se divida entre 0
		{
			std::cout << RED << "ERROR: Cannot divide by Zero" << END_COLOR << std::endl;
			return false;
		}
		result = stack1 / stack2;
		std::cout << YELLOW << "DIVIE: \t" << END_COLOR << stack1 << "/" << stack2 << "=" << result << std::endl;
	}
	else
	{
		std::cout << RED << "ERROR: Invalid Operator" << END_COLOR << std::endl;
		return false;
	}
	stack.push(result);
	return true;
}

void RPN::printResult(const char* operations) const
{
	std::string str(operations);
	float result = stack.top();

	std::cout << GREEN << "\nResultado:\n" << END_COLOR << result << std::endl;
}
