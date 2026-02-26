#include "MateriaSource.class.hpp"

MateriaSource::MateriaSource( void ) : _usedSlots(0) {}; 

MateriaSource::~MateriaSource( void ) {
	for (unsigned int i = 0; i < _usedSlots; i++) {
		delete _inventory[i];
	}
}

void		MateriaSource::learnMateria( AMateria *m ) {
	if (_usedSlots == _numSlots)
		return ;
	_inventory[_usedSlots++] = m->clone();
}

AMateria*	MateriaSource::createMateria( std::string const & type ) {
	for (unsigned int i = 0; i < _usedSlots; i++)
		if (_inventory[i]->getType() == type)
			return _inventory[i]->clone();
	return 0;
}
