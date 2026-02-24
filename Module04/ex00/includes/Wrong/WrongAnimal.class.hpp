#pragma once

#include <string>

class WrongAnimal {

protected:
	std::string	_type;

	WrongAnimal( std::string type );
	WrongAnimal( WrongAnimal const &other );
	
	WrongAnimal	&operator=( WrongAnimal const &other );
	void		_announceMethod(std::string methodName,
					  std::string className = "WrongAnimal");

public:
	WrongAnimal( void );
	virtual ~WrongAnimal( void );

	void	makeSound( void ) const;
	void	getType( void ) const;
};
