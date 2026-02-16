#include "Brain.class.hpp"

#include <iostream>

void	Brain::_announceMethod( std::string methodName) {
	std::cout << "# Brain #" << methodName << " Called." << std::endl;
}

Brain::Brain( Brain &other ) {

	_announceMethod("Copy Constructor");
	for (int i = 0; i < _maxIdeas; i++) {
		ideas[i] = other.ideas[i];
	}
}

Brain&	Brain::operator=( Brain &other ) {

	_announceMethod("Copy Operator");
	if (this != &other)
		for (int i = 0; i < _maxIdeas; i++)
			ideas[i] = other.ideas[i];
	return ( *this );
}

// Public Members

Brain::Brain( void ) {
	_announceMethod("Constructor");
}

Brain::~Brain( void ) { 
	_announceMethod("Destructor");
}
