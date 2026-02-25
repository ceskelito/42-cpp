#include "MateriaStorage.class.hpp"

MateriaStorage::MateriaStorage ( void ) : _usedStorage(0) {};

MateriaStorage::~MateriaStorage ( void ) {

	for (unsigned int i = 0; i < _usedStorage; i++) {
		delete _storage[i];
	}
}

// Public Member Functions

void	MateriaStorage::put( AMateria *m ) {
	
	if (_usedStorage == _maxStorage) {
		delete _storage[_usedStorage--];
	}
	_storage[_usedStorage++] = m;
}

AMateria*	MateriaStorage::take( unsigned int const idx ) {

	AMateria	*tmp;

	if ( idx >= _usedStorage )
		return ( NULL );

	tmp = _storage[idx];
	_storage[idx] = NULL;
	for (unsigned int i = idx; i < _usedStorage - 1; i++) {
		_storage[i] = _storage[i + 1];
	}
	return ( tmp );
}
