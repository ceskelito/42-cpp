#pragma once

#include "Weapon.hpp"

class HumanA {

private:
	string	_name;
	Weapon&	_weapon;

public:
	HumanA(string name, Weapon &weapon);
	void	attack(void);
};
