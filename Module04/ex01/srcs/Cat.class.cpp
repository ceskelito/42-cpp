#include "Cat.class.hpp"

#include <iostream>

Cat::Cat( void ): Animal("Cat") {
	_announceMethod("Constructor", "Cat");
}

Cat::~Cat( void ) {
	_announceMethod("Destructor", "Cat");
}

Cat::Cat( Cat &other ): Animal(other) {
	_announceMethod("Copy Constructor", "Cat");
}

void	Cat::makeSound( void ) {
	std::cout << "Meow" << std::endl;
}
