#include "ClapTrap.class.hpp"
#include <iostream>

using std::cout;
using std::endl;

ClapTrap::ClapTrap(void) : 
	_name("defaultName"),
	_hitPoints(10),
	_energyPoints(10),
	_attackDamage(0) {
	
	cout << "ClapTrap void constructor called" << endl;
}

ClapTrap::ClapTrap(string name) : 
	_name(name),
	_hitPoints(10),
	_energyPoints(10),
	_attackDamage(0) {
	
	cout << "ClapTrap parametrized constructor called" << endl;
}

ClapTrap::~ClapTrap(void) {
	cout << "ClapTrap destructor called" << endl;
}

// Private Member Functions

void	ClapTrap::_subEnergy(unsigned int amount) {
	_energyPoints -= amount;
}

void	ClapTrap::_subHit(unsigned int amount) {
	_hitPoints -= amount;
}

void	ClapTrap::_gainEnergy(unsigned int amount) {
	_energyPoints += amount;
}

void	ClapTrap::_gainHit(unsigned int amount) {
	_hitPoints += amount;
}

// Public Member Functions

void	ClapTrap::attack(const string &target) {
	_subEnergy(1);
	cout << "ClapTrap " << _name << " attacks " << target <<
		", causing " << _attackDamage << " points of damage!" << endl;
}

void	ClapTrap::takeDamage(unsigned int amount) {
	_subHit(amount);
	cout << "ClapTrap " << _name << " has be attacked " <<
		", taking " << amount << " points of damage!" << endl;
}

void	ClapTrap::beRepaired(unsigned int amount) {
	_subEnergy(1);
	cout << "ClapTrap " << _name << " repaired itself " <<
		", gaining " << amount << " hit points!" << endl;
}
