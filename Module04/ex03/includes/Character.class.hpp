#pragma once

#include "AMateria.class.hpp"

class Character: public ICharacter {

private:
	enum { _numSlots = 4 };

	AMateria*	_inventory[_numSlots];
	int			_usedSlots;
	std::string	_name;

	void	_archiveMateria( AMateria* m );

public:
	Character ( void );
	Character ( Character &other );
	Character ( std::string name );
	~Character ( void );
	Character&	operator=( Character &other );

	std::string	const & getName() const ;

	void	equip(AMateria* m);
	void	unequip(int idx);
	void	use(int idx, ICharacter& target);


};
