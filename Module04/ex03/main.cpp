#include <iostream>

#include "Character.class.hpp"
#include "MateriaSource.class.hpp"
#include "Ice.class.hpp"
#include "Cure.class.hpp"

using std::cout;
using std::endl;

int main ( void ) {

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

	return 0;
}
