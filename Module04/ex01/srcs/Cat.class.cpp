#include "Cat.class.hpp"

#include <iostream>

Cat::Cat( void ): Animal("Cat") {
	_announceMethod("Constructor", "Cat");
	_brain = new Brain();
}

Cat::~Cat( void ) {
	_announceMethod("Destructor", "Cat");
	delete _brain;
}

Cat::Cat( Cat &other ): Animal(other) {
	_announceMethod("Copy Constructor", "Cat");
	_brain = new Brain(*other._brain);
}

Cat&	Cat::operator=( Cat &other ) {
	_announceMethod("Copy operator", "Cat");

	if (this != &other) {
		_type = other._type;
		delete _brain;
		_brain = new Brain(*other._brain);
	}
	return ( *this );
}

void	Cat::makeSound( void ) const {
	std::cout << "Meow" << std::endl;
}
