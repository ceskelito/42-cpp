#include "AAnimal.class.hpp"

#include <iostream>
#include <iomanip>

#define GENERIC_ANIMAL_TYPE "genericAAnimal"

void	AAnimal::_announceMethod(std::string methodName, std::string className) {
	int delta = 10 - className.length();
	int wid1 = delta / 2;
	int wid2 = (delta % 2 == 0) ? wid1 : wid1 + 1;

	std::cout << std::setw(wid1) << std::left << "|" << className << std::setw(wid2) << std::right <<  "|";
	std::cout << " - [" << this->_type << "] " << methodName << " Called." << std::endl;
}

AAnimal::AAnimal( void ): _type(GENERIC_ANIMAL_TYPE) {
	_announceMethod("Constructor");
}

AAnimal::AAnimal( std::string type ): _type(type) {
	_announceMethod("Constructor");
}

AAnimal::~AAnimal( void ) {
	_announceMethod("Destructor");
}

AAnimal::AAnimal( AAnimal const &other ): _type(other._type) {
	_announceMethod("Copy Constructor");
}

AAnimal& AAnimal::operator=( AAnimal const &other ) {
	_announceMethod("Copy Operator");
	_type = other._type;
	return (*this);
}

void	AAnimal::makeSound( void ) const {
	std::cout << "genericAAnimal is not a real animal and do not make any sound." << std::endl;
}

std::string	AAnimal::getType( void ) const {
	return ( _type );
}
