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

Character& Character::operator=( Character &other ) {
	tmp = Character(other);
}

void	Character::equip( AMateria* m ) {

	if ( _usedSlots < _numSlots )
		_inventory[_usedSlots++] = m;
	else
		_ground.put(m);
}

void	Character::unequip(unsigned int const idx ) {
	if (!_inventory[idx])
		return ;

	_ground.put( _inventory[idx] );
	_inventory[idx] = NULL;

	for (unsigned int i = idx; i < _usedSlots - 1; i++)
		_inventory[i] = _inventory[i + 1];
}
