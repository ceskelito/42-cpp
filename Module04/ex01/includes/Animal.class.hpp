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
	~Animal( void );

	void	makeSound( void );
	void	getType( void );
};
