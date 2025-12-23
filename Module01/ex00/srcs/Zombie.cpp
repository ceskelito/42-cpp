#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(std::string name): _name(name) {};

Zombie::~Zombie(void) {
	std::cout << _name << " has died (again).";
}

void Zombie::announce(void) {
	std::cout << _name << ": BraiiiiiiinnnzzzZ...";
}


