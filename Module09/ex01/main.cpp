#include "RPN.hpp"

#include <iostream>

int main( int ac, char **av ) {
	if ( ac != 2 )
	{
		std::cerr << "Error: requested one argument." << std::endl;
		return 1;
	}
	try {
		long r = RPN(av[1]);
		std::cout << r << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
