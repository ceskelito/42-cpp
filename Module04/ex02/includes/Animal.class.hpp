#pragma once

#include <string>

class Animal {

protected:
	std::string	_type;

	Animal( std::string type );
	Animal( Animal const &other );
	
	Animal	&operator=( Animal const &other );
	void	_announceMethod(std::string methodName,
					  std::string className = "Animal");

public:
	Animal( void );
	virtual ~Animal( void );

	virtual void	makeSound( void ) const;
	virtual Animal*	clone( void ) const;
	std::string		getType( void ) const;
};
