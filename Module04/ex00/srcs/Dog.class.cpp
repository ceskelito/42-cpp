#include "Dog.class.hpp"

#include <iostream>

Dog::Dog( void ): Animal("Dog") {
	_announceMethod("Constructor", "Dog");
}

Dog::~Dog( void ) {
	_announceMethod("Destructor", "Dog");
}

Dog::Dog( Dog &other ): Animal(other) {
	_announceMethod("Copy Constructor", "Dog");
}

void	Dog::makeSound( void ) {
	std::cout << "Bau!" << std::endl;
}
