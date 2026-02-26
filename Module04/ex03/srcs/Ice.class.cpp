#include <iostream>

#include "Ice.class.hpp"

static std::string const g_type = "ice";

Ice::Ice( void ) : AMateria( g_type ) {};
Ice::Ice( Ice const &other ) : AMateria( other ) {};
Ice::~Ice( void ) {};

Ice & Ice::operator=( Ice &other ) {
	if (this != &other) {
		this->_type = other._type;
	}
	return *this;
};

AMateria * Ice::clone( void ) const {
	AMateria *tmp = new Ice( *this );

	return tmp;
}

void	Ice::use( ICharacter &target ) {
	std::cout << "* shoots an ice bolt at " << target.getName() << " *";	
}
