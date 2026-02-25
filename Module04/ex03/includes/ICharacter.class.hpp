#pragma once

#include <string>

class AMateria;

class ICharacter {

public:

	virtual ~ICharacter() {}
	virtual std::string const & getName() const = 0;
	virtual void equip(AMateria* m) = 0;
	virtual void unequip(unsigned int const idx) = 0;
	virtual void use(unsigned int const idx, ICharacter& target) = 0;
};
