#pragma once

#include "AMateria.class.hpp"

class MateriaStorage {

private:
	enum { _maxStorage = 1024 };

	unsigned int	_usedStorage ;
	AMateria*		_storage[_maxStorage];

public:

	MateriaStorage ( void );
	~MateriaStorage ( void );

	void		put( AMateria *m );
	AMateria*	take( unsigned int const idx );

};
