#pragma once

#include "ICharacter.class.hpp"

#include <string>


class AMateria {

protected:
	std::string	_type;

	AMateria ( void );
	AMateria ( AMateria &other );
	AMateria&	operator=( AMateria &other );

public:
	virtual ~AMateria ( void );

	AMateria(std::string const & type);
	//[...]
	std::string const & getType() const; //Returns the materia type
	virtual AMateria* clone() const = 0;
	virtual void use(ICharacter& target);
};
