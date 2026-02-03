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

Fixed::Fixed(const float value) : _rawBits(roundf(value * (1 << _numFractional))) {
// To undestand the conversion
//
// 1. Understand the bit layout
//
//	The float value is NOT converted by manipulating its IEEE 754 bit layout.
//	We will only use the mathematical value of the float.
//
//	In example:
//	  Decimal: 5.25
//	  Mathematical binary form: 0..10101
//
//	We'll dig down in this example later.
//
// 2. The shift logic
//
//	From this value, conceptually, it is like moving
//	the binary point 8 positions to the left (assuming _numFractional as 8).
//	In practice, we scale the number by 2^8 to encode it as fixed-point.
//	The binary point is NOT moved and NOT stored: it is implicit.
//
//	Remember:
//	  n * (1 << X) == n * 2^X
//	  n / (1 << X) == n * 2^-X
//	
//	This works like scientific notation, but in base 2.
//	Shifting does not move a point: it scales the integer value.
//	
//	Basically "Moves the bits in the opposite direction
//	of where you want to (conceptually) move the point".
//	
//	The interpretation of the bits depends on how many fractional bits
//	we assume (_numFractional).
//
// 3. The example
//	
//	Notice: after the point, the weights will be negatives (2 1 0 . -1 -2 ...).
//	
//	Decimal: 5.25
//	Mathematical binary form: 101.01 (the point is implicit)
//		5   -> 101	-> 2^2 + 2^0 
//		0.5 -> .01	-> 2^-2
//
//	The operation:
//	         5.25 *    256  = 1344
//	  00000010101 * 1 << 8  = 10101000000
//
//	We know where to place the point -> 101.01000000 ==> 5.25
//
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

// Public member functions

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

//  1 << X == 2 ^ X
float Fixed::toFloat(void) const {
	return ((float)_rawBits / (1 << _numFractional));
}

// External function

std::ostream &operator<<(std::ostream &os, const Fixed &f) {
	os << f.toFloat();
	return (os);
}
