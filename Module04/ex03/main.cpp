#include <iostream>
#include <iomanip>

#include "Character.class.hpp"
#include "MateriaSource.class.hpp"
#include "Ice.class.hpp"
#include "Cure.class.hpp"

using std::cout;
using std::endl;

void equip_use_unequip( void ) {
	
	ICharacter *me = new Character("rick");

	Character mike("mike");
	Character bianca("bianca");

	MateriaSource src;

	src.learnMateria(new Ice());
	src.learnMateria(new Cure());

	cout << mike.getName() << " is equipping Ice!" << endl;
	mike.equip(src.createMateria("ice"));
	cout << bianca.getName() << " equip's Cure." << endl;
	bianca.equip(src.createMateria("cure"));

	cout << me->getName() << " is equipping Ice!" << endl;
	me->equip(src.createMateria("ice"));
	cout << me->getName() << " equip's Cure." << endl;
	me->equip(src.createMateria("cure"));

	cout << me->getName() << "'s turn: ";
	me->use(0, mike);
	
	cout << mike.getName() << "'s turn: ";
	mike.use(0, *me);
	cout << bianca.getName() << "'s turn: ";
	bianca.use(0, mike);

	cout << me->getName() << "'s turn: ";
	me->use(1, *me);

	cout << me->getName() << " drops his cure." << endl;
	me->unequip(1);

	delete me;
}

void clone_and_copy( void ) {
	ICharacter	*original = new Character("ori");
	ICharacter	*second(original);
	ICharacter	*third = second;

	cout << std::setw(12) << "original : "<< original << endl;
	cout << std::setw(12) << "second : "<< second << endl;
	cout << std::setw(12) << "third : "<< third << endl;
}

int main ( void ) {

	cout << "Basic usage: " << endl << endl;
	equip_use_unequip();
	cout << endl << "---------------" << endl << endl;
	cout << "Cloning and coping: " << endl << endl;
	clone_and_copy();
	return 0;
}
