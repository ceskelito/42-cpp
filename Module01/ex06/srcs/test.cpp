#include "Harl.class.hpp"
#include <iostream>

int main(int ac, char **av)
{
	Harl harl;

	if (ac != 2)
	{
		std::cout << "Error: invalid number of arguments";
		return (1);
	}
	else {
		harl.complain(av[1]);
	}
}
