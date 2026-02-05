#include <cmath>
#include "Fixed.class.hpp"

/* Public member functions */

int Fixed::getRawBits(void) const {
	return (this->_rawBits);
}

void Fixed::setRawBits(const int raw) {
	this->_rawBits = raw;
}

int Fixed::toInt(void) const {
	return (_rawBits >> _numFractional);
}

float Fixed::toFloat(void) const {
	return ((float)_rawBits / (1 << _numFractional));
}
