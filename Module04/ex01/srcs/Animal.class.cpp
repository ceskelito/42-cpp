#include "Animal.class.hpp"

#include <iostream>
#include <iomanip>

void	Animal::_announceMethod(std::string methodName, std::string className) {
	int delta = 10 - className.length();
	int wid1 = delta / 2;
	int wid2 = (delta % 2 == 0) ? wid1 : wid1 + 1;

	std::cout << std::setw(wid1) << std::left << "|" << className << std::setw(wid2) << std::right <<  "|";
	std::cout << " - [" << this->_type << "] " << methodName << " Called." << std::endl;
}

Animal::Animal( void ): _type("genericAnimal") {
	_announceMethod("Constructor");
}

Animal::Animal( std::string type ): _type(type) {
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

void	Animal::makeSound( void ) {
	std::cout << "genericAnimal is not a real animal and do not make any sound." << std::endl;
}

std::string	Animal::getType( void ) {
	return ( _type );
}
