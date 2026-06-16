#include <iostream>
#include <fstream>

int main(int ac, char **av) {
	if (ac != 2)
	{
		std::cerr << "Erroneus number of argument. Has to be 1." << std::endl;
		return 1;
	}
	std::ifstream	file;
	file.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	try {
		file.open(av[1]);
		// resto della logica
	}
	catch (std::ios_base::failure &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

}
