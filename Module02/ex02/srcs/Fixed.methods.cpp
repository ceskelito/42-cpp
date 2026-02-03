#include <iostream>
#include <cmath>
#include "Fixed.class.hpp"

using std::cout;
using std::endl;

/* Public member functions */

int Fixed::getRawBits(void) const {
	cout << "getRawBits member function called" << endl;
	return (this->_rawBits);
}

void Fixed::setRawBits(const int raw) {
	cout << "setRawBits member function called" << endl;
	this->_rawBits = raw;
}

int Fixed::toInt(void) const {
	return (_rawBits >> _numFractional);
}

float Fixed::toFloat(void) const {
	return ((float)_rawBits / (1 << _numFractional));
}
