#include "WrongAnimal.class.hpp"

#include <iostream>
#include <iomanip>

void	WrongAnimal::_announceMethod(std::string methodName, std::string className) {
	int delta = 15 - className.length();
	int wid1 = delta / 2;
	int wid2 = (delta % 2 == 0) ? wid1 : wid1 + 1;

	std::cout << std::setw(wid1) << std::left << "|" << className << std::setw(wid2) << std::right <<  "|";
	std::cout << " - [" << this->_type << "] " << methodName << " Called." << std::endl;
}

WrongAnimal::WrongAnimal( void ): _type("genericWrongAnimal") {
	_announceMethod("Constructor");
}

WrongAnimal::WrongAnimal( std::string type ): _type(type) {
	_announceMethod("Constructor");
}

WrongAnimal::~WrongAnimal( void ) {
	_announceMethod("Destructor");
}

WrongAnimal::WrongAnimal( WrongAnimal const &other ): _type(other._type) {
	_announceMethod("Copy Constructor");
}

WrongAnimal& WrongAnimal::operator=( WrongAnimal const &other ) {
	_announceMethod("Copy Operator");
	_type = other._type;
	return (*this);
}

void	WrongAnimal::makeSound( void ) const {
	std::cout << "genericWrongAnimal is not a real animal and do not make any sound." << std::endl;
}

void	WrongAnimal::getType( void ) const {
	std::cout << _type << std::endl;
}
