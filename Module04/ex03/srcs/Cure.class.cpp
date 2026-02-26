#include <iostream>

#include "Cure.class.hpp"

static std::string const g_type = "cure";

Cure::Cure( void ) : AMateria( g_type ) {};
Cure::Cure( Cure const &other ) : AMateria( other ) {};
Cure::~Cure( void ) {};

Cure & Cure::operator=( Cure &other ) {
	if (this != &other) {
		this->_type = other._type;
	}
	return *this;
};

AMateria * Cure::clone( void ) const {
	AMateria *tmp = new Cure( *this );

	return tmp;
}

void	Cure::use( ICharacter &target ) {
	std::cout << "* heals " << target.getName() << "’s wounds *" << std::endl;
}
