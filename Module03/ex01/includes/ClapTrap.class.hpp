#pragma once

#include <string>

using std::string;

class ClapTrap {

protected:
	string			_name;
	unsigned int	_hitPoints;
	unsigned int	_energyPoints;
	unsigned int	_attackDamage;

	void	_subEnergy(unsigned int amount);
	void	_subHit(unsigned int amount);

	void	_gainEnergy(unsigned int amount);
	void	_gainHit(unsigned int amount);
	
	ClapTrap(void);

public:

	// Constructors / Destructor
	ClapTrap(string name);
	~ClapTrap(void);

	ClapTrap(const ClapTrap &other);
	ClapTrap	&operator=(const ClapTrap &other);

	// Member functions
	void	attack(const string &target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
};
