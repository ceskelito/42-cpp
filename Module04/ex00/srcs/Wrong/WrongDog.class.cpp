#include "WrongDog.class.hpp"

#include <iostream>

WrongDog::WrongDog( void ): WrongAnimal("WrongDog") {
	_announceMethod("Constructor", "WrongDog");
}

WrongDog::~WrongDog( void ) {
	_announceMethod("Destructor", "WrongDog");
}

WrongDog::WrongDog( WrongDog &other ): WrongAnimal(other) {
	_announceMethod("Copy Constructor", "WrongDog");
}

void	WrongDog::makeSound( void ) {
	std::cout << "Bau!" << std::endl;
}
