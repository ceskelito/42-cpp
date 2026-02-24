#include "Brain.class.hpp"

#include <iostream>
#include <iomanip>

void	Brain::_announceMethod( std::string methodName) {
	std::string	className = "Brain";
	int			delta = 10 - className.length();
	int			wid1 = delta / 2;
	int			wid2 = (delta % 2 == 0) ? wid1 : wid1 + 1;

	std::cout << std::setw(wid1) << std::left << "#" << className << std::setw(wid2) << std::right <<  "#";
	std::cout << " - " << methodName << " Called." << std::endl;
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
