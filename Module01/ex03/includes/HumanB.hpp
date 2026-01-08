#pragma once

#include "Weapon.hpp"

class HumanB {

private:
	string	_name;
	Weapon*	_weapon;

public:
	HumanB(string name);
	HumanB(string name, Weapon &weapon);

	void	attack(void);
	void	setWeapon(Weapon &weapon);
};
