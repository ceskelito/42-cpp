#pragma once

#include <string>

class AAnimal {

protected:
	std::string	_type;

	AAnimal( std::string type );
	AAnimal( AAnimal const &other );
	
	AAnimal	&operator=( AAnimal const &other );
	void	_announceMethod(std::string methodName,
					  std::string className = "AAnimal");

public:
	AAnimal( void );
	virtual ~AAnimal( void );

	virtual void		makeSound( void ) const = 0;
	virtual AAnimal*	clone( void ) const = 0;
	std::string			getType( void ) const;
};
