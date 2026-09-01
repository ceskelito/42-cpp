// #include "PmergeMe.hpp"
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

// #include "PmergeMe.hpp"

#include "debugUtils.hpp"

#include "PmergeMe.hpp"
#include <cmath>
#include <cstdlib>

extern int g_cmps;

int F(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}

int main( int ac, char **av ) {
	if ( ac != 2 )
	{
		std::cerr << "Error: requested one argument." << std::endl;
		return 1;
	}
	// try{
	// 	time_t	timeUsed = PmergeMe(extractNumbersDeque(av[1]));
	// 	std::cout << "Time used to order: " << timeUsed << std::endl;
	// }
	// catch (std::exception &e) {
	// 	std::cerr << "Error: " << e.what() << std::endl;
	// }
	std::deque<int> firstStep = ford_johnson(extractNumbersDeque(av[1]));
	std::cout << std::endl << "MAIN" << std::endl;
	debug::printDeque(firstStep);

	std::cout << std::endl << std::endl;
	std::cout << "Expected : " << F(firstStep.size()) << std::endl;
	std::cout << "Effective: " << g_cmps << std::endl;
}
