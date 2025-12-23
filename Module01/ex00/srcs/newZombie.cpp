#include "Zombie.hpp"

Zombie *newZombie(std::string name) {

	Zombie *ptr = NULL;

	*ptr = Zombie(name);

	return ptr;
}
