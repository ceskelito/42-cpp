#pragma once

#include <string>

class Animal {

protected:
	std::string	_type;
	void		_announceMethod(std::string methodName);

public:
	Animal( void );
	~Animal( void );

	Animal( Animal &other );
	Animal &operator=( Animal &other );

	void	makeSound( void );
};
