#pragma once

#include "ICharacter.class.hpp"

#include <string>


class AMateria {

protected:
	std::string	_type;

	AMateria ( void );
	AMateria ( AMateria const &other );
	AMateria (std::string &type);
	AMateria (std::string const &type);

public:
	virtual ~AMateria ( void );

	std::string const & getType() const; //Returns the materia type
	virtual AMateria* clone() const = 0;
	virtual void use(ICharacter& target);
};
