#pragma once

#include "Animal.class.hpp"

class Dog: virtual public Animal {

private:
	using	Animal::_announceMethod;

public:
	using Animal::operator=;
	
	Dog( void );
	~Dog( void );
	Dog( Dog &other );
	
	void	makeSound( void );
};
