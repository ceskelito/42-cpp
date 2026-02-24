#pragma once

#include "WrongAnimal.class.hpp"

class WrongDog: virtual public WrongAnimal {

private:
	using	WrongAnimal::_announceMethod;

public:
	using WrongAnimal::operator=;
	
	WrongDog( void );
	~WrongDog( void );
	WrongDog( WrongDog &other );
	
	void	makeSound( void );
};
