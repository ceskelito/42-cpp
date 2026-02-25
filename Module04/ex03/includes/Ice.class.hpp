#pragma once

#include "AMateria.class.hpp"

class Ice: public AMateria{

private:
	using AMateria::_type;

public:
	
	Ice( void );
	Ice( Ice const &other );
	~Ice( void );

	Ice& operator=( Ice &other);

	AMateria*	clone( void ) const;
	void		use( ICharacter& target );

};
