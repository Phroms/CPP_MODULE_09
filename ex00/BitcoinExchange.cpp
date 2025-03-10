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

// Metodo para encontrar la fecha
bool Bitcoin::found_date(const std::string &date)
{
	std::stringstream ss(date);
	std::string value;
	int day;
	int month;
	int year;

	// Obtener el year
	if (!std::getline(ss, value, '-') || !isDigitStr(value) || value.length() != 4)
		return false;
	std::istringstream(value) >> year; // Convierte la cadena en un numero y lo guarda en year

	// Obtener el month
	if (!std::getline(ss, value) || !isDigitStr(value))
		return false;
	std::istringstream(value) >> month; // Convierte la cadena en un numero y lo guarda en month
	
	// Obtener el day
	if (!std::getline(ss, value))
		return false;
	std::istringstream(value) >> day; // Convierte la cadena en un numero y lo guarda en day
	
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

void Bitcoin::parse(Bitcoin &data, const char* file)
{
	(void)data;
	std::fstream fs;
	std::string line;

	fs.open(file, std::fstream::in); //fstream::in es un modo que solo le indica que leera ese archivo(tambien esta out que le servira para escribir)

	if (!fs.is_open())
	{
		throw std::logic_error("Failed to open input text");
	}
	while (std::getline(fs, line))
		std::cout << line << std::endl;
	fs.close();
	
}

 
