#include <iostream>
#include <cmath>
#include "Fixed.class.hpp"

using std::cout;
using std::endl;

Fixed &Fixed::operator=(const Fixed &other) {
	cout << "Copy assignement operator calld" << endl;
	if (this != &other)
		this->_rawBits = other._rawBits;
	return (*this);
}

/* Comparison operators */

bool	Fixed::operator>(const Fixed &other) const {
	return (_rawBits > other._rawBits);
}

bool	Fixed::operator<(const Fixed &other) const {
	return (_rawBits < other._rawBits);
}

bool	Fixed::operator>=(const Fixed &other) const {
	return (_rawBits >= other._rawBits);
}

bool	Fixed::operator<=(const Fixed &other) const {
	return (_rawBits <= other._rawBits);
}

bool	Fixed::operator==(const Fixed &other) const {
	return (_rawBits == other._rawBits);
}
bool	Fixed::operator!=(const Fixed &other) const {
	return (_rawBits != other._rawBits);
}	

/* Arithmetic operators */

Fixed	Fixed::operator+(const Fixed &other) const {
	Fixed result;
	result.setRawBits(this->_rawBits + other._rawBits);
	return (result);
}

Fixed	Fixed::operator-(const Fixed &other) const {
	Fixed result;
	result.setRawBits(this->_rawBits - other._rawBits);
	return (result);
}

Fixed	Fixed::operator*(const Fixed &other) const {
	Fixed		result;
	long long	this_tmp = this->_rawBits;
	long long	other_tmp = other._rawBits;

	result.setRawBits((this_tmp * other_tmp) >> 8);
	return (result);
}

Fixed	Fixed::operator/(const Fixed &other) const {
	Fixed		result;
	long long	tmp = this->_rawBits << 8;

	result.setRawBits((int)(tmp / other._rawBits));
	return (result);
}

/*  Increment/Decrement operators */

	// Pre
Fixed	&Fixed::operator++(void) {
	this->_rawBits++;
	return (*this);
}
Fixed	&Fixed::operator--(void) {
	this->_rawBits--;
	return (*this);
}

	// Post
Fixed	Fixed::operator++(int) {
	Fixed tmp(*this);

	this->_rawBits++;
	return (tmp);
}
Fixed	Fixed::operator--(int) {

	Fixed tmp(*this);

	this->_rawBits--;
	return (tmp);
}
