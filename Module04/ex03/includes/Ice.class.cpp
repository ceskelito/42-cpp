#pragma once

#include "AMateria.class.hpp"

class Ice: public AMateria{

private:

public:
	
	Ice( void );
	Ice( Ice &other );
	~Ice( void );

	Ice& operator=( Ice &other);

	AMateria*	clone( void );
	void		use( ICharacter& target );

};
