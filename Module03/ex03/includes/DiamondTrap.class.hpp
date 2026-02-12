#pragma once

#include "ScavTrap.class.hpp"
#include "FragTrap.class.hpp"

class DiamondTrap : public ScavTrap, public FragTrap {

private:
	string	_name;

	DiamondTrap( void );

public:

	using	FragTrap::_hitPoints;
	using	ScavTrap::_energyPoints;
	using	FragTrap::_attackDamage;

	using	ScavTrap::attack;

	DiamondTrap( string name );
	~DiamondTrap( void );

	void    whoAmI( void );
};
