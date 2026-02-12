#include "ScavTrap.class.hpp"
#include <iostream>

using std::cout;
using std::endl;

ScavTrap::ScavTrap(string name): ClapTrap(name) { 

	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 20;
	cout << "< ScavTrap > - " << _name << " has been born." << endl;
}

ScavTrap::~ScavTrap(void) {
	cout << "< ScavTrap > - " << _name << " has been destroyed." << endl;
}

void    ScavTrap::attack( std::string const& target )
{
    if (_energyPoints <= 0)
    {
        cout << "< ScavTrap > - " << _name << " is out of energy! It cannot attack." << endl;
        return;
    }
    cout << "< ScavTrap > - " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << endl;
	_subEnergy();
}

void    ScavTrap::guardGate() {
    cout << "< ScavTrap > - " << _name << " is now in Gate keeper mode." << endl;
}
