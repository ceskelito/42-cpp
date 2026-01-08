#include "HumanB.hpp"

#include <iostream>

HumanB::HumanB(string name):
	_name(name)
	{};

HumanB::HumanB(string name, Weapon &weapon):
	_name(name),
	_weapon(&weapon)
	{};

void	HumanB::attack(void) {
	std::cout << _name << " attacks with their " << _weapon->getType() << std::endl;
}

void	HumanB::setWeapon(Weapon &weapon) {
	_weapon = &weapon;
}
