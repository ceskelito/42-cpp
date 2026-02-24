#pragma once

#include "AAnimal.class.hpp"
#include "Brain.class.hpp"

class Dog: virtual public AAnimal {

private:
	using	AAnimal::_announceMethod;

	Brain	*_brain;

public:
	
	Dog( void );
	~Dog( void );
	Dog( Dog const &other );

	Dog&	operator=( Dog const &other );
	void	makeSound( void ) const;

	AAnimal*	clone( void ) const;
};
