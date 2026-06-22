#include "BitcoinExchange.hpp"
#include <iostream>
#include <exception>

int main(int ac, char **av) {
	if (ac != 2)
	{
		std::cerr << "Erroneus number of argument. Has to be 1." << std::endl;
		return 1;
	}

	try {
		BitcoinExchange btc(av[1]);
		btc.printExchange();
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
