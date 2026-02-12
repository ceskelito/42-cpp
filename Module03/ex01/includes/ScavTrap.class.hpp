#pragma once

#include "ClapTrap.class.hpp"

class ScavTrap : public ClapTrap {

private:
	ScavTrap(void);
	
public:

	// Constructors / Destructor
	ScavTrap(string name);
	~ScavTrap(void);

	// Member Functions
	void	guardGate(void);
	void	attack(string const &target);
};
