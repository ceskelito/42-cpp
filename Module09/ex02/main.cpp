#include "PmergeMe.hpp"

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>

time_t	PmergeMe(std::vector<int> sequence);
time_t	PmergeMe(std::deque<int> sequence);

std::vector<int> extractNumbers(const std::string& input) {

    std::vector<int>	numbers;
    std::istringstream	iss(input);
    int					n;

    while (iss >> n) {
		if (n < 0)
			throw std::invalid_argument("Not a positive number.");
		numbers.push_back(n);
	}

	if (!iss.eof())
		throw std::invalid_argument("Not a number.");

    return numbers;
}

std::deque<int> extractNumbersDeque(const std::string& input) {

    std::deque<int>	numbers;
    std::istringstream	iss(input);
    int					n;

    while (iss >> n) {
		if (n < 0)
			throw std::invalid_argument("Not a positive number.");
		numbers.push_back(n);
	}

	if (!iss.eof())
		throw std::invalid_argument("Not a number.");

    return numbers;
}

int main( int ac, char **av ) {
	if ( ac != 2 )
	{
		std::cerr << "Error: requested one argument." << std::endl;
		return 1;
	}
	try{
		time_t	timeUsed = PmergeMe(extractNumbersDeque(av[1]));
		std::cout << "Time used to order: " << timeUsed << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
