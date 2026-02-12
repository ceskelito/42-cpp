#include "ClapTrap.class.hpp"

int main(void) {
	ClapTrap	example;
	ClapTrap	clap("clap");

	clap.attack("NoNameSelected");
	example.takeDamage(5);
	example.beRepaired(3);
}
