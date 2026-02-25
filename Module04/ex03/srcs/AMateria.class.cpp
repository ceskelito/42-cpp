#include "AMateria.class.hpp"

AMateria::AMateria ( void ) : _type("none") {};

AMateria::AMateria ( AMateria const &other ): _type(other._type) {};

AMateria::AMateria ( std::string const type ): _type(type) {};

AMateria::~AMateria ( void ) {};

Amateria::AMateria& operator=( AMateria & other ) {};
