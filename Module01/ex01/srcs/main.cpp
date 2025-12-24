#include "Zombie.h"
#include "Zombie.hpp"
#include <iostream>

static const int			N_ZOMBIES = 10;
static const std::string	NAME = "John Cena";

int	main(void)
{
	Zombie	*horde = zombieHorde(N_ZOMBIES, NAME);

	for (int i = 0; i < N_ZOMBIES; i++) {
		horde[i].announce();
	}

	std::cout << std::endl;

	for (int i = 0; i < N_ZOMBIES; i++) {
		horde[i].~Zombie();
	}

	operator delete [] (horde);
}
