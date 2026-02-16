#include "Animal.class.hpp"

#include <iostream>

void	Animal::_announceMethod(std::string methodName) {
	std::cout << "[ " << this->_type << " ]" << methodName << " Called." << std::endl;
}

Animal::Animal( void ): _type("genericAnimal") {
	_announceMethod("Constructor");
}

Animal::~Animal( void ) {
	_announceMethod("Destructor");
}

Animal::Animal( Animal &other ): _type(other._type) {
	_announceMethod("Copy Constructor");
}

Animal& Animal::operator=( Animal &other ) {
	_announceMethod("Copy Operator");
	_type = other._type;
	return (*this);
}
