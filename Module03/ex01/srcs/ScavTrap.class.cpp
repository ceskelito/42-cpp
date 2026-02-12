#include "ScavTrap.class.hpp"
#include <iostream>

using std::cout;
using std::endl;

ScavTrap::ScavTrap(void) : 
	ClapTrap(),
	_name("defaultName"),
	_hitPoints(100),
	_energyPoints(50),
	_attackDamage(20) {
	
	cout << "ScavTrap void constructor called" << endl;
}

ScavTrap::ScavTrap(string name) : 
	_name(name),
	_hitPoints(100),
	_energyPoints(50),
	_attackDamage(20) {
	
	cout << "ScavTrap parametrized constructor called" << endl;
}

ScavTrap::~ScavTrap(void) {
	cout << "ScavTrap destructor called" << endl;
}
