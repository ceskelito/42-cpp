#include "Cat.class.hpp"

#include <iostream>

const std::string Cat::_className = "Cat";

// void	Cat::_announceMethod(std::string methodName) {
// 	std::cout << "[ " << this->_type << " ]" << methodName << " Called." << std::endl;
// }

Cat::Cat( void ): Animal("Cat") {
	_announceMethod("Constructor", "Cat");
}

Cat::~Cat( void ) {
	_announceMethod("Destructor", "Cat");
}

// Cat::Cat( Cat &other ): _type(other._type) {
// 	_announceMethod("Copy Constructor");
// }
//
// Cat& Cat::operator=( Cat &other ) {
// 	_announceMethod("Copy Operator");
// 	_type = other._type;
// 	return (*this);
// }

void	Cat::makeSound( void ) {
	std::cout << "Meow" << std::endl;
}
