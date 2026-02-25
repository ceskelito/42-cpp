#pragma once

#include "AMateria.class.hpp"

#include <string>

class ICharacter {

public:

	virtual ~ICharacter() {}
	virtual std::string const & getName() const = 0;
	virtual void equip(AMateria* m) = 0;
	virtual void unequip(unsigned int const idx) = 0;
	virtual void use(unsigned int const idx, ICharacter& target) = 0;
};
