#include <iostream>
#include <cmath>
#include "Fixed.class.hpp"

using std::cout;
using std::endl;

Fixed::Fixed(void) : _rawBits(0) {
	cout << "Default constructor called" << endl;
}

Fixed::Fixed(const Fixed &other) : _rawBits(other._rawBits) {
	cout << "Copy constructor called" << endl;
}

Fixed::Fixed(const int value) : _rawBits(value << _numFractional) {
	cout << "Integer constructor called" << endl;
}

Fixed::Fixed(const float value) : _rawBits(roundf(value) * (1 << _numFractional)) {
	cout << "Float constructor called" << endl;
}

Fixed::~Fixed(void) {
	cout << "Destructor called" << endl;
}

Fixed &Fixed::operator=(const Fixed &other) {
	cout << "Copy assignement operator calld" << endl;
	if (this != &other)
		this->_rawBits = other._rawBits;
	return (*this);
}

std::ostream &Fixed::operator<<(std::ostream &os) {
	os << this->toFloat();
	return (os);
}

// Public member functions

int Fixed::getRawBits(void) const {
	cout << "getRawBits member function called" << endl;
	return (this->_rawBits);
}

void Fixed::setRawBits(const int raw) {
	cout << "setRawBits member function called" << endl;
	this->_rawBits = raw;
}

int Fixed::toInt(void) {
	return (_rawBits >> _numFractional);
}

float Fixed::toFloat(void) {
	return ((float)_rawBits / (1 << _numFractional));
}

