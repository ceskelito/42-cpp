#include "Zombie.h"
#include "Zombie.hpp"

static const int			N_ZOMBIES = 10;
static const std::string	NAME = "John Ceena";

int	main(void)
{
	Zombie	*horde = zombieHorde(N_ZOMBIES, NAME);

	for (int i = 0; i < N_ZOMBIES; i++) {
		horde[i].announce();
	}

	for (int i = 0; i < N_ZOMBIES; i++) {
		horde[i].~Zombie();
	}

	delete [] horde;
}
