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

	cout << "Creating new character and equipping with ice..." << endl;
	ICharacter	*original = new Character("ori");
	MateriaSource src;
	src.learnMateria(new Ice);
	original->equip(src.createMateria("ice"));

	cout << "Creating two copies, one from the original, one from the second..." << endl;
	Character	second = *dynamic_cast<Character*>(original);
	ICharacter	*third = new Character(*dynamic_cast<Character*>(original));

	cout << "Memory addresses of the three Characters: " << endl;
	cout << std::setw(12) << "original : "<< original << " - name : " << original->getName() << endl;
	cout << std::setw(12) << "second : "<< &second << " - name : " << second.getName() << endl;
	cout << std::setw(12) << "third : "<< third << " - name : " << third->getName() << endl;

	cout << endl << "Now we'll delete the original." << endl;
	delete original;

	cout << "Attempting to use itmes from a copy, after deleting the original:" << endl;
	cout << std::setw(12) << "second : ";
	second.use(0, *third); 
	cout << std::setw(12) << "second : ";
	third->use(0, second);
}

int main ( void ) {

	cout << "Basic usage: " << endl << endl;
	equip_use_unequip();
	cout << endl << "---------------" << endl << endl;
	cout << "Cloning and coping: " << endl << endl;
	clone_and_copy();
	return 0;
}
