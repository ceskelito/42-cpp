#pragma once

#include "ClapTrap.class.hpp"

class FragTrap : public ClapTrap {

private:
	FragTrap(void);

public:
	FragTrap(string name);
	~FragTrap(void);

	void highFivesGuys( void );
};
