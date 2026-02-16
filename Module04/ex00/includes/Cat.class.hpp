#pragma once

#include "Animal.class.hpp"

#include <string>

class Cat: virtual public Animal {

private:
	using	Animal::_announceMethod;

	static const std::string	_className;

public:
	Cat( void );
	~Cat( void );
	//
	// Cat( Cat &other );
	using Animal::operator=;

	void	makeSound( void );
};
