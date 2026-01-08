#include "HumanA.hpp"

#include <iostream>

HumanA::HumanA(string name, Weapon &weapon):
	_name(name),
	_weapon(weapon)
	{};

void	HumanA::attack(void) {
	std::cout << _name << " attacks with their " << _weapon.getType() << std::endl;
}
