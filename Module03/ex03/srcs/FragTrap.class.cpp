#include "FragTrap.class.hpp"
#include <iostream>

using std::cout;
using std::endl;

FragTrap::FragTrap( string name ): ClapTrap(name) { 

	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
	cout << "| FragTrap | - " << _name << " has been born." << endl;
}

FragTrap::~FragTrap( void ) {
	cout << "| FragTrap | - " << _name << " has been destroyed." << endl;
}

void    FragTrap::highFivesGuys( void ) {
    if ( _energyPoints <= 0 ) {
        cout << "| FragTrap | - " << _name << " is out of energy. It cannot high fives the guys." << endl;
        return;
    }
    cout << "| FragTrap | - " << _name << " high fives everybody." << endl;
	_subEnergy();
}
