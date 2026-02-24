#pragma once

#include "WrongAnimal.class.hpp"

class WrongCat: virtual public WrongAnimal {

private:
	using	WrongAnimal::_announceMethod;

public:
	using WrongAnimal::operator=;
	
	WrongCat( void );
	~WrongCat( void );
	WrongCat( WrongCat &other );
	
	void	makeSound( void );
};
