#pragma once

#include <string>

using std::string;

class ClapTrap {

protected:
	string	_name;
	int		_hitPoints;
	int		_energyPoints;
	int		_attackDamage;

	void	_subEnergy(unsigned int amount);
	void	_subHit(unsigned int amount);

	void	_gainEnergy(unsigned int amount);
	void	_gainHit(unsigned int amount);

public:

	// Constructors / Destructor
	ClapTrap(void);
	ClapTrap(string name);
	~ClapTrap(void);

	// Member functions
	void	attack(const string &target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
};
