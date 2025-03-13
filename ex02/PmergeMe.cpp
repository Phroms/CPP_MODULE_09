# include "PmergeMe.hpp"
#include <algorithm>
#include <cstddef>

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
				std::cout << GREEN << "\nGrupo formado: " << vec[i] << " " << vec[i + 1] << END_COLOR << std::endl;
			}
			else // Si el primer elemento es mayor o igual al segundo, lo anadimos en orden descendete
			{
				// ejemplo: vec = "50 30"
				pares.push_back(vec[i + 1]); // anadimos el segundo elemento(menor => 30)
				pares.push_back(vec[i]); // anadimos el primer elemento(mayor => 50)
				// lo que deberia quedar es (30, 50)
				std::cout << GREEN << "\nGrupo formado 2: " << vec[i + 1] << " " << vec[i] << END_COLOR << std::endl;
			}
		}
		else // Si no hay par (es decir, estamos en el ultimo elemento sin pareja(osea un numero solo))
		{
			pares.push_back(vec[i]); // anadimos el ultimo elemento solo, ya que no tiene par
			std::cout << GREEN << "\nElemento solo: " << vec[i] << END_COLOR << std::endl;
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

void PmergeMe::sortDeque(const std::deque<int> &deq)
{
	if (deq.size() <= 1)
		return ;

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
