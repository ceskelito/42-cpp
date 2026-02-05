#include <iostream>
#include <cmath>
#include "Fixed.class.hpp"

/* Output Stream operator */

std::ostream &operator<<(std::ostream &os, const Fixed &f) {
	os << f.toFloat();
	return (os);
}

/* Assignement operator */

Fixed &Fixed::operator=(const Fixed &other) {
	if (this != &other)
		_rawBits = other._rawBits;
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
	result.setRawBits(_rawBits + other._rawBits);
	return (result);
}

Fixed	Fixed::operator-(const Fixed &other) const {
	Fixed result;
	result.setRawBits(_rawBits - other._rawBits);
	return (result);
}

Fixed	Fixed::operator*(const Fixed &other) const {
	Fixed		result;
	long long	this_raw = _rawBits;
	long long	other_raw = other._rawBits;

	result.setRawBits((this_raw * other_raw) >> 8);
	return (result);
}

Fixed	Fixed::operator/(const Fixed &other) const {
	Fixed		result;
	long long	tmp = _rawBits << 8;

	result.setRawBits((int)(tmp / other._rawBits));
	return (result);
}

/*  Increment/Decrement operators */

	// Pre
Fixed	&Fixed::operator++(void) {
	_rawBits++;
	return (*this);
}
Fixed	&Fixed::operator--(void) {
	_rawBits--;
	return (*this);
}

	// Post
Fixed	Fixed::operator++(int) {
	Fixed tmp(*this);

	_rawBits++;
	return (tmp);
}
Fixed	Fixed::operator--(int) {

	Fixed tmp(*this);

	_rawBits--;
	return (tmp);
}
