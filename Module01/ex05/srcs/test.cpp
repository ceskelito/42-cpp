#include "Harl.class.hpp"
#include <iostream>

int main(void)
{
	Harl harl;	

	harl.complain("DEBUG");
	std::cout << std::endl;
	harl.complain("INFO");
	std::cout << std::endl;
	harl.complain("WARNING");
	std::cout << std::endl;
	harl.complain("ERROR");
}
