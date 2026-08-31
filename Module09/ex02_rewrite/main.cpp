// #include "PmergeMe.hpp"
#include "PmergeMe_impl.hpp"
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

#include <cmath>
int F(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}

// #include "PmergeMe.hpp"

#include "debugUtils.hpp"

#include "PmergeMe.hpp"

int main( int ac, char **av ) {
	if ( ac != 2 )
	{
		std::cerr << "Error: requested one argument." << std::endl;
		return 1;
	}
	try {
		std::deque<int> dq = extractNumbersDeque(av[1]);
		unsigned long dqComparisons = 0;
		std::deque<int> firstStep = ford_johnson_with_count(dq, dqComparisons);
		std::cout << std::endl << "MAIN (deque)" << std::endl;
		debug::printDeque(firstStep);
		std::cout << std::endl << "Comparisons (deque): " << dqComparisons << std::endl;

		std::vector<int> vec = extractNumbers(av[1]);
		unsigned long vecComparisons = 0;
		std::vector<int> vecResult = ford_johnson_with_count_template< std::vector, int, std::allocator<int> >(vec, vecComparisons);
		std::cout << std::endl << "MAIN (vector)" << std::endl;
		for (std::vector<int>::iterator it = vecResult.begin(); it != vecResult.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl << "Comparisons (vector): " << vecComparisons << std::endl;

		std::cout << std::endl << "Comparisons (expected): " << F(vec.size()) << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
}
