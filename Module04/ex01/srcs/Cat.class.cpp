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
	_brain = other._brain;
}

Cat&	Cat::operator=( Cat &other ) {
	_announceMethod("Copy operator", "Cat");

	_type = other._type;
	_brain = other._brain;
	return ( *this );
}

void	Cat::makeSound( void ) {
	std::cout << "Meow" << std::endl;
}
