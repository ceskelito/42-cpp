#pragma once

#include "AMateria.class.hpp"
#include "MateriaStorage.class.hpp"

class Character: public ICharacter {

private:
	static MateriaStorage	_ground;
	enum { _numSlots = 4 };

	AMateria*		_inventory[_numSlots];
	unsigned int	_usedSlots;
	std::string		_name;

	void	_archiveMateria( AMateria* m );


public:
	Character ( void );
	Character ( Character &other );
	Character ( std::string name );
	~Character ( void );
	Character&	operator=( Character &other );

	std::string	const & getName() const ;

	void	equip(AMateria* m);
	void	unequip(unsigned int const idx);
	void	use(unsigned int const idx, ICharacter& target);
};
