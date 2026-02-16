#pragma once

#include "Animal.class.hpp"
#include "Brain.class.hpp"

class Dog: virtual public Animal {

private:
	using	Animal::_announceMethod;

	Brain	*_brain;

public:
	
	Dog( void );
	~Dog( void );
	Dog( Dog &other );

	Dog&	operator=( Dog &other );
	void	makeSound( void ) const;
};
