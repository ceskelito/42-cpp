#include "Character.class.hpp"

/* Costructors / Destructor */

Character::Character( void ): _usedSlots(0), _name("defaultName") {};
Character::Character( Character const &other ): _usedSlots(0), _name(other._name) {};
Character::Character( std::string const name ): _usedSlots(0), _name(name) {};

Character::~Character( void ) {
	for (unsigned int i =0; i < _usedSlots; i++) {
		delete _inventory[i];
	}
};

Character& Character::operator=( Character const &other ) {
	Character	*tmp = new Character(other);
	return *tmp;
}

/* Public Member Functions */

std::string const	&Character::getName( void ) const {
	return _name;
}

/* Inventory Member Functions */

void	Character::equip( AMateria* m ) {

	if (!m)
		return ;
	if ( _usedSlots < _numSlots )
		_inventory[_usedSlots++] = m;
	else
		_ground.put(m);
}

void	Character::unequip(unsigned int const idx ) {
	if ( idx >= _usedSlots )
		return ;

	_ground.put( _inventory[idx] );
	_inventory[idx] = NULL;
	_usedSlots--;

	for (unsigned int i = idx; i < _usedSlots - 1; i++) {
		_inventory[i] = _inventory[i + 1];
		_inventory[i + 1] = NULL;
	}
}

void	Character::use(unsigned int const idx, ICharacter &target) {
	if ( idx >= _usedSlots )
		return ;
	_inventory[idx]->use(target);
}
