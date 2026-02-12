#include "DiamondTrap.class.hpp"

#include <iostream>

using std::cout;
using std::endl;

DiamondTrap::DiamondTrap( string name ) : ClapTrap(name), ScavTrap (name), FragTrap (name) {

	_name = name;
	ClapTrap::_name = name + "_clap_name";

	cout << "# DiamondTrap # - " << _name << " constructed." << endl;
}

DiamondTrap::~DiamondTrap() {
    cout << "# DiamondTrap # - " << _name << " destructed." << endl;
}

void    DiamondTrap::whoAmI( void ) {
    cout << "I am a DiamondTrap named " << _name << ", ClapTrap name: " << ClapTrap::_name << endl;
}
