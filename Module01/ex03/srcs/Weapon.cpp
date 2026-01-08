#include "Weapon.hpp"

Weapon::Weapon(string type): _type(type) {};

string	Weapon::getType(void) {
	return _type;
}

void	Weapon::setType(string type) {
	_type = type;
}
