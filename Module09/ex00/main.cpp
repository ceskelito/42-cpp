#include "BitcoinExchange.hpp"
#include <iostream>

int main(int ac, char **av) {
	if (ac != 2)
	{
		std::cerr << "Erroneus number of argument. Has to be 1." << std::endl;
		return 1;
	}

	BitcoinExchange btc(av[1]);
	btc.printInfo();
}
