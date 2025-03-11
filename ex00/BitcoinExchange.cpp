# include "BitcoinExchange.hpp"

Bitcoin::Bitcoin(){}

Bitcoin::Bitcoin(const Bitcoin &cpy)
{
	*this = cpy;
}

Bitcoin &Bitcoin::operator=(const Bitcoin &rhs)
{
	if (this != &rhs)
	{
		data.clear();
		data = rhs.data;
	}
	return *this;
}

Bitcoin::~Bitcoin() {}

// Funcion que eliminara los espacio alrededor de la string
std::string trimString(const std::string &str)
{
	size_t first = str.find_first_not_of(" "); // metodo que encuentra los espacios al principio de la string
	size_t last = str.find_last_not_of(" "); // metodo que encuentra los espacios al final de la string

	return str.substr(first, last - first + 1); // hacemos una substring con los espacios eliminados + 1, para el ultimo caracter
}

// Funcion para verificar que la cadena solo tiene numeros
static bool isDigitStr(const std::string &str)
{
	size_t pos = str.find_first_not_of("0123456789");

	if (pos != std::string::npos) // npos devolvera la posicion en el caso de encontrar algun caracter no numerico, caso contrario devuelve true
	{
		throw std::invalid_argument("A non-numeric character was found");
	}
	return true;
}

// Metodo para obtener la tasa de Bitcoin mas cercana a una fecha dada
float Bitcoin::getRate(const std::string &date) const
{
	std::map<std::string, float>::const_iterator it;

	it = data.lower_bound(date); // lower_bound te encuentra la fecha igual o mayor
	if (it == data.end() || it ->first != date) // Si leyo toda la data hasta el final o si es distinto la data enviada, entrara en el segundo if
	{
		if (it == data.begin()) // Si dentro de la data esta la fecha solicitada retornara el valor, pero si no esta hara un -- y se ira a la mas cercana o mejor dicho mayor
			return 0; // No hay fechas previas
		it--; // Retrocede a la fecha mas cercana anterior
	}
	return it->second; // Retorna la data encontrada
}

// Cargar la data de un archivo CSV
bool Bitcoin::found_file(const char* file)
{
	std::ifstream myFile (file);
	std::string line;

	if (!myFile.is_open())
	{
		throw std::logic_error("Failed to open dataBase(DB)");
	}

	while (std::getline(myFile, line))
	{
		std::stringstream ss(line); // Se utiliza para dividir la linea en partes
		std::string date; // La primera parte dividida antes de la coma se guarda en date (que es la fecha).
		float value; // La segunda parte dividida despues de la coma se guarda en value (que es el valor numerico).

		if (std::getline(ss, date, ',') && ss >> value) // Leera hasta la ',' ya que se veria que son fechas y las almacenara en date, y despues de la coma almacenara lo demas en value ("2022-04-02,45000.75")
		{ // date = 2022-04-02 ; value = 45000.75
			data[date] = value; // Guarda date y value en el mapa = data
		}
	}
	myFile.close();
	return true;
}

// Funcion para ver el year biciesto
bool isleasteYear(int year)
{
	if (year % 400 == 0) // Si el year divisible por 400, es biciesto
		return true;

	if (year % 100 == 0) // Si el year es divisible por 100 pero no por 400, no es biciesto
		return false;

	if (year % 4 == 0) // Si el year es divisible por 4, es biciesto
		return true;

	return false;
}

// Funcion para encontrar la fecha
bool found_date(const std::string &date)
{
	std::stringstream ss(date);
	std::string value;
	int day;
	int month;
	int year;

	// Obtener el year
	if (std::getline(ss, value, '-'))
	{
		if (!isDigitStr(value) || value.length() != 4)
			return false;
		std::istringstream key(value);
		if (!(key >> year)) // Se intenta convertir la string a un numero entero
			return false;
	}
	else
		return false;

	// Obtener el month
	if (std::getline(ss, value, '-'))
	{
		if (!isDigitStr(value) || value.length() != 2)
			return false;
		std::istringstream key(value);
		if (!(key >> month))
			return false;
	}
	else
		return false;
	
	// Obtener el day
	if (std::getline(ss, value))
	{
		if (!isDigitStr(value) || value.length() != 2)
			return false;
		std::istringstream key(value);
		if (!(key >> day))
			return false;
	}
	else
		return false;
	
	// Validar month y day
	if (month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	// Validar year
	if ((month == 4 ||  month == 6 || month == 9 || month == 11) && day == 31)
		return false;

	// Validar February
	if (month == 2)
	{
		int leasteYear = isleasteYear(year);
		if ((leasteYear && day > 29) || (!leasteYear && day > 28))
			return false;
	}
	return true;
}

// Metodo para hacer una conversion de string a float
float strToFloat(const std::string &valueStr)
{
	std::stringstream ss(valueStr); // stringstream = almacena toda una string que le envies; (en este caso se almacena valueStr en ss)
	float value;

	ss >> value; // Intenta extraer un numero de float de ss y almacenarlo en value
	
	if (ss.fail()) // Verifica si ocurrio un error en la conversion
	{
		throw std::invalid_argument("Invalid number format");
	}
	
	return value; // Retorna el numero convertido
}

// Procesar archivo de entrada
bool Bitcoin::parse(const char* fileName) const
{
	std::ifstream file(fileName); // Esta linea crea un objeto ifstream llamado file, que se usa para leer archivos

	if (!file.is_open()) // Si no se pudo abrir el archivo, damos el throw que indicara el error
	{
		throw std::logic_error("Failed to open input text");
	}
	
	std::string line; // Creamos una string llamada line para almacenar cada linea leida del archivo
	bool firstLine = true; // Un booleano que se usa para saltarse la primera linea leida del archivo
	
	while (std::getline(file, line)) // lee una linea del archivo y la almacena en line hasta llegar al final del archivo
	{
		if (firstLine) // Si es la primera linea del archivo, se marca con false y se usa continue para saltarse esa linea
		{
			firstLine = false;
			continue; // Saltarse la primera linea
		}
		std::istringstream inputLine(line); // Crea un objeto istringstream llamado inputLine que permite leer desde la cadena line
		std::string date; // Una variable de tipo string para almacenar la fecha (date)
		std::string valueStr; // Una variable de tipo string para almacenar el valor (variable)
		
		// (!str::getline(inputLine, date, '|'))
		// esta Funcion lee desde la entrada de inputLine(que es la linea que hemos leido del archivo)
		// hasta encontrar '|' y la almacenara en date 
		// ejemplo: "2020-12-10|500.0" -> date = "2020-03-10"
		if (!std::getline(inputLine, date, '|') || !std::getline(inputLine, valueStr))
		{
			// Despues de haber leido la fecha getline Intenta leer el resto de la linea(despues de '|')
			// y lo coloca en la variable "valueStr"
			// ejemplo: "2020-12-10|500.0" -> valueStr = "500.0"
			std::cerr << RED << "ERROR: " << END_COLOR << "Entrada invalida => " << line << std::endl;
			continue;
		}

		date = trimString(date); // Con la Funcion trimString eliminamos los espacios en blanco al princio de la string
		valueStr = trimString(valueStr); // Con la Funcion trimString eliminamos los espcaions en blanco al final de la string	
		
		try
		{
			if (!found_date(date)) // Si la fecha no es valida, lanzamos la excepcion
			{
				throw std::invalid_argument("Invalid date => " + date);
			}
			float value = strToFloat(valueStr); // Se convierte la string valueStr a un numero de punto flotante (float)
			if (value < 0 || value > 1000)
			{
				throw std::invalid_argument("Number out of range => " + valueStr);
			}

			float rate = getRate(date); // Se obtiene la tasa de cambio correspondiente a la fecha mediante la funcion getRate y getRate devuelve el valor para esa fecha
			std::cout << date << " => " << value << " = " << value * rate << std::endl;
			// Si todo fue correcto, se imprime la fecha, el valor original y el resultado de la multiplicacion de ese valor por la tasa de cambio obtenida
		}
		catch (const std::exception &e) // Se lanza una exception cuando ocurre un fallo
		{
			std::cerr << e.what() << std::endl;
		}
	}
	file.close();
	return true;
}

 
