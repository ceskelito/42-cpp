#pragma once

#include "AMateria.class.hpp"

class Cure: public AMateria{

private:
	using AMateria::_type;

public:
	
	Cure( void );
	Cure( Cure const &other );
	~Cure( void );

	Cure& operator=( Cure &other);

	AMateria*	clone( void ) const;
	void		use( ICharacter& target );

};
