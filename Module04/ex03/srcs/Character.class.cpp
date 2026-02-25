#include "Character.class.hpp"

// static void initCharacterSlots( AMateria *s[], int numSlots ) {
//
// 	for (int i = 0; i < numSlots, i++) {
// 		//
// 	}
//
// }

Character::Character( void ): _usedSlots(0), _name("defaultName") {};

Character::Character( Character &other ): _usedSlots(0), _name(other._name) {};
Character::Character( std::string name ): _usedSlots(0), _name(name) {};
Character::~Character( void ) {};


void	Character::_archiveMateria( AMateria* m ) {
	// idk if is needed this function, maybe -
	// i can use a list to take track of every -
	// unused materia present in the program.
	//
	// I need to study a little more to accomplish -
	// this task int the most cpp-ish manner possible.
	// A linked list sounds this much c-ish... ew, boomer!
}

void	Character::equip( AMateria* m ) {

	if ( _usedSlots < _numSlots )
		_inventory[_usedSlots++] = m;
	else
	 /*save the materia somewhere (maybe a list?) */;
}

void	Character::unequip( int idx ) {
	if (_inventory[idx] /*is NULL ???*/) {
		
	}
}
