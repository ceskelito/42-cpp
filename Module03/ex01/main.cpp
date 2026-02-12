#include "ClapTrap.class.hpp"

int main(void) {
	ClapTrap	bob("Bob");
	ClapTrap	clappp("Clappp");
	ClapTrap	bob2(bob);
	ClapTrap	clappp2("Clappp2");

	clappp2 = clappp;

	clappp.attack("Bob");
	bob.takeDamage(5);
	bob.beRepaired(3);
}
