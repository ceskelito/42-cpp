#pragma once

#include <ostream>

class Fixed {

private:
	int					_rawBits;
	static const int	_numFractional = 8;

public:

	// Constructors / Destructor
	Fixed(void);
	Fixed(const Fixed &other);
	Fixed(const int value);
	Fixed(const float value);
	~Fixed(void);

	// Getter / Setter
	int		getRawBits(void) const;
	void	setRawBits(const int raw);

	// Conversion
	int		toInt(void) const;
	float	toFloat(void) const;


	// Static member functions
	static Fixed		&min(Fixed &a, Fixed &b);
	static Fixed		&max(Fixed &a, Fixed &b);
	static const Fixed	&min(const Fixed &a, const Fixed &b);
	static const Fixed	&max(const Fixed &a, const Fixed &b);

	/* Operators overload */

	// Assignement operator
	Fixed	&operator=(const Fixed &other);
	
	// Comparison operators
	bool	operator>(const Fixed &other) const;
	bool	operator<(const Fixed &other) const;
	bool	operator>=(const Fixed &other) const;
	bool	operator<=(const Fixed &other) const;
	bool	operator==(const Fixed &other) const;
	bool	operator!=(const Fixed &other) const;

	// Arithmetic operators
	Fixed	operator+(const Fixed &other) const;
	Fixed	operator-(const Fixed &other) const;
	Fixed	operator*(const Fixed &other) const;
	Fixed	operator/(const Fixed &other) const;

	// Increment/Decrement operators

	// -Pre
	Fixed	&operator++(void);	
	Fixed	&operator--(void);	
	// -Post
	Fixed	operator++(int);
	Fixed	operator--(int);
};
	
std::ostream &operator<<(std::ostream &os, const Fixed &f);
