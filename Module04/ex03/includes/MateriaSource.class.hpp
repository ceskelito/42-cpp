#pragma once

#include "IMateriaSource.class.hpp"
#include "MateriaStorage.class.hpp"

class MateriaSource : public IMateriaSource {

	private:
		MateriaStorage	_ground;
		enum { _numSlots = 4 };

		unsigned int	_usedSlots;
		AMateria*		_inventory[_numSlots];

	public:
		MateriaSource ( void ) ; 
		~MateriaSource ( void ) ;

		void		learnMateria(AMateria* m);
		AMateria*	createMateria(std::string const & type);
};
