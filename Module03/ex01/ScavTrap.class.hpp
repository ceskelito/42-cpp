#pragma once

#include "ClapTrap.class.hpp"

class ScavTrap : public ClapTrap {
	
public:
	ScavTrap(void);
	ScavTrap(string name);
	~ScavTrap(void);

	// Member Functions
	void	guardGate(void);
};
