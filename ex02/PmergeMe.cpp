# include "PmergeMe.hpp"
#include <ctime>

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

void PmergeMe::sortVector(std::vector<int> &vec)
{
	if (vec.size() <= 1)
		return ;

	std::vector<int> pares;
	for (size_t i = 0; i < vec.size(); i += 2) // Esto significa que la i avanza de 2 en 2, apuntando a los elementos en las posiciones 0, 2, 4, 6, etc.
	{
		if (i + 1 < vec.size()) // Esto es para que no exceda el tamano, si el contenido de mi vector es 10 y 20, lo hace para que no vea mas alla de eso como un 30 o otros numeros
		{
			if (vec[i] < vec[i + 1]) // Si el primer elemento del par es menor que el segundo, lo anadimos en orden ascendente
			{
				// ejemplo: vec = "40 60 20 10", el resultado abajo de la linea
				pares.push_back(vec[i]); // anadimos el primer elemento(menor => 40) (menor => 10)
				pares.push_back(vec[i + 1]); // anadimos el segundo elemento(mayor => 60) (mayor => 20)
				// lo que deberia quedar es (40, 60) ; (10, 20)
				std::cout << BLUE << "\nGrupo formado: " << END_COLOR << vec[i] << " " << vec[i + 1] << std::endl;
			}
			else // Si el primer elemento es mayor o igual al segundo, lo anadimos en orden descendete
			{
				// ejemplo: vec = "50 30"
				pares.push_back(vec[i + 1]); // anadimos el segundo elemento(menor => 30)
				pares.push_back(vec[i]); // anadimos el primer elemento(mayor => 50)
				// lo que deberia quedar es (30, 50)
				std::cout << BLUE << "\nGrupo formado 2: " << END_COLOR << vec[i + 1] << " " << vec[i] << std::endl;
			}
		}
		else // Si no hay par (es decir, estamos en el ultimo elemento sin pareja(osea un numero solo))
		{
			pares.push_back(vec[i]); // anadimos el ultimo elemento solo, ya que no tiene par
			std::cout << BLUE << "\nElemento solo: " << END_COLOR << vec[i] << std::endl;
		}
	}

	// Creamos dos grupos, 'pend' para los numeros bajos y 'main' para los altos
	std::vector<int> pend, main;

	for (size_t i = 0; i < pares.size(); i += 2) // Recorremos de dos en dos
	{
		pend.push_back(pares[i]); // anadimos el primer elemento del par a 'pend'
		
		if (i + 1 < pares.size()) // verificamos que haya un segundo elemento para evitar el desbordamiento
		{
			main.push_back(pares[i + 1]); // anadimos el segundo elemento del par a 'main'
		}
	}

	// Aplicamos Merge-Insertion
	// Ordena con sort(algoritmo de ordenacion rapida de STL)
	std::sort(main.begin(), main.end()); // Ordena los elementos en 'main'
	
	// Copia los elementos ordenados de 'main' al vector original 'vec' 
	vec = main;

	// Insertar los elementos de 'pend' en 'vec' en la posición correcta
	for (size_t i = 0; i < pend.size(); i++)
	{
		std::vector<int>::iterator it = std::lower_bound(vec.begin(), vec.end(), pend[i]);
		vec.insert(it, pend[i]); // Insertar cada elemento en orden correcto
	}

	std::cout << CYAN << "\nVector Ordenado: " << END_COLOR;
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::sortDeque(std::deque<int> &deq)
{
	if (deq.size() <= 1)
		return ;

	std::deque<int> pares; // Creamos un deque llamado pares, para almacenar los pares ordenados
	
	std::deque<int>::const_iterator it = deq.begin(); // Un iterator para recorrer el deque

	while (it != deq.end()) // Bucle para ordenar los pares y ordenarlos
	{
		int first = *it; // Tomamos el primer numero del par
		it++; // Avanzamos con el iterator
		if (it == deq.end()) // Si llegamos al final significa que encontramos un numero solo
		{
			pares.push_back(first); // Guardamos el numero solo
			break; // Salimos del Bucle
		}

		int second = *it; // Tomamos el segundo numero del par
		it++; // Avanzamos el iterator al siguiente par
		
		// Ordenamos el par antes de almacenarlo en 'pares'
		if (first < second)
		{
			pares.push_back(first); // numero bajo primero
			pares.push_back(second); // numero alto despues
		}
		else
		{
			pares.push_back(second); // numero alto primero
			pares.push_back(first); // numero bajo despues
		}
	}

	// Creamos dos grupos: 'pend' para los numeros bajos y 'main' para los mayores
	std::deque<int> pend, main;

	// Variable para alternar entre los dos grupos
	bool addToLeft = true;

	// Recorremos los elementos de 'pares' usando un iterator normal
	for (std::deque<int>::iterator it = pares.begin(); it != pares.end(); it++)
	{
		if (addToLeft)
		{
			pend.push_back(*it); // Agregamos a 'pend'
		}
		else
		{
			main.push_back(*it); // Agregamos a 'main'
		}
		addToLeft = !addToLeft; // Es una alteracion que al principio addToLeft es true
		// y con esta linea va cambiando su valor si es true, cambia a false, si es false cambia a true
		// y eso lo hace para indicar a los elementos a que bloque ir, si es true va a pend(numeros bajos)
		// si es false va main(numeros altos)
	}
	// Ordenamos los elementos en 'main' usando std::sort
	std::sort(main.begin(), main.end());

	// Pasamos el contenido de 'main' a 'deq'
	deq = main;

	// Insertamos los elementos de 'pend' end 'deq' en la posición correcta
	for (std::deque<int>::iterator it = pend.begin(); it != pend.end(); it++)
	{
		// Buscamos la posición correcta usando busqueda binaria
		std::deque<int>::iterator insertPost = std::lower_bound(deq.begin(), deq.end(), *it);
		deq.insert(insertPost, *it); // Insertamos el numero en el lugar correcto
	}
	std::cout << CYAN << "\nDeque Ordenado: " << END_COLOR;
	for (size_t i = 0; i < deq.size(); i++)
	{
		std::cout << deq[i] << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::calculateTime(std::vector<int> &vec, std::deque<int> &deq)
{
	// Time vec
	clock_t start_vec = clock();

	sortVector(vec);

	clock_t final_vec = clock();

	double resultVec = ((double) (final_vec - start_vec)) / CLOCKS_PER_SEC * 10;

	// Time deque
	clock_t start_deq = clock();

	sortDeque(deq);

	clock_t final_deq = clock();

	double resultDeq = ((double) (final_deq - start_deq)) / CLOCKS_PER_SEC * 10;

	std::cout << GREEN << "\nTime vec: " << END_COLOR << resultVec << std::endl;
	std::cout << GREEN << "\nTime deq: " << END_COLOR << resultDeq << std::endl;
}

void PmergeMe::printVect(const std::vector<int> &vec)
{
	std::cout << YELLOW << "\nPrint Vector: " << END_COLOR;

	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::printDeqe(const std::deque<int> &deq)
{
	std::cout << YELLOW << "\nPrint Deque: " << END_COLOR;
	for (size_t i = 0; i < deq.size(); i++)
	{
		std::cout << deq[i] << " ";
	}
	std::cout << std::endl;
}
