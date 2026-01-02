#include "Zombie.hpp"

Zombie	*zombieHorde( int N, std::string name ) {

	Zombie	*horde = static_cast<Zombie *> (operator new[](N * sizeof(Zombie)));
	// Zombie	*horde = (Zombie *) (operator new[] (N * sizeof(Zombie)));

	for (int i = 0; i < N; i++) {
		new (&horde[i]) Zombie(name);
	}

	return horde;
}
