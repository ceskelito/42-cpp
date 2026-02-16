#pragma once

#include <string>

class Animal {

protected:
	std::string	_type;

	Animal( std::string type );
	Animal( Animal &other );
	
	Animal	&operator=( Animal &other );
	void	_announceMethod(std::string methodName,
					  std::string className = "Animal");

public:
	Animal( void );
	virtual ~Animal( void );

	virtual void	makeSound( void ) const;
	virtual Animal*	clone( void ) const = 0;
	std::string		getType( void ) const;
};
