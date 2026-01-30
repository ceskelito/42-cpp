#include <iostream>
#include "../includes/Fixed.class.hpp"

using std::cout;
using std::endl;

Fixed::Fixed(void) : _rawBits(0) {
	cout << "Default constructor called" << endl;
}

Fixed::Fixed(const Fixed &other) : _rawBits(other._rawBits) {
	cout << "Copy constructor called" << endl;
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

// Methods

int Fixed::getRawBits(void) const {
	return (this->_rawBits);
}

void Fixed::setRawBits(const int raw) {
	this->_rawBits = raw;
}

