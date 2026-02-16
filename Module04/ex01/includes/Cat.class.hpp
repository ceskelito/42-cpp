#pragma once

#include "Animal.class.hpp"
#include "Brain.class.hpp"

class Cat: virtual public Animal {

private:
	using	Animal::_announceMethod;

	Brain	*_brain;

public:
	
	Cat( void );
	~Cat( void );
	Cat( Cat &other );

	Cat&	operator=( Cat &other );
	void	makeSound( void );
};
