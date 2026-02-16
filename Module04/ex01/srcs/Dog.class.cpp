#include "Dog.class.hpp"

#include <iostream>

Dog::Dog( void ): Animal("Dog") {
	_announceMethod("Constructor", "Dog");
	_brain = new Brain();
}

Dog::~Dog( void ) {
	_announceMethod("Destructor", "Dog");
	delete _brain;
}

Dog::Dog( Dog &other ): Animal(other) {
	_announceMethod("Copy Constructor", "Dog");
	_brain = new Brain(*other._brain);
}

Dog&	Dog::operator=( Dog &other ) {
	_announceMethod("Copy operator", "Dog");

	if (this != &other) {
		_type = other._type;
		delete _brain;
		_brain = new Brain(*other._brain);
	}
	return ( *this );
}

void	Dog::makeSound( void ) const {
	std::cout << "Bau!" << std::endl;
}
