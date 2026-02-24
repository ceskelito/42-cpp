#include "WrongCat.class.hpp"

#include <iostream>

WrongCat::WrongCat( void ): WrongAnimal("WrongCat") {
	_announceMethod("Constructor", "WrongCat");
}

WrongCat::~WrongCat( void ) {
	_announceMethod("Destructor", "WrongCat");
}

WrongCat::WrongCat( WrongCat &other ): WrongAnimal(other) {
	_announceMethod("Copy Constructor", "WrongCat");
}

void	WrongCat::makeSound( void ) {
	std::cout << "Meow" << std::endl;
}
