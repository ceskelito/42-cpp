#pragma once

#include "Animal.class.hpp"

class Cat: virtual public Animal {

private:
	using	Animal::_announceMethod;

public:
	using Animal::operator=;
	
	Cat( void );
	~Cat( void );
	Cat( Cat &other );
	

	void	makeSound( void );
};
