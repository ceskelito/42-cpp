#pragma once

#include "AMateria.class.hpp"

class Character: public ICharacter {

private:
	enum { _numSlots = 4 };

	AMateria	_inventory[_numSlots];
	std::string	_name;

public:
	Character ( void );
	Character ( Character &other );
	~Character ( void );
	Character&	operator=( Character &other );

	Character ( std::string name );

};
