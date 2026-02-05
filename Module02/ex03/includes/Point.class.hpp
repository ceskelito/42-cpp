#pragma once

#include "Fixed.class.hpp"

class Point {

	private:

	Fixed const	_x;
	Fixed const	_y;

	public:

	// Constructors / Destructor
	Point(void);
	Point(const float x, const float y);
	Point(Point const &other);
	~Point(void);

	// Operators overload
	Point	&operator=(Point const &other);

	// Public methods
	Fixed	x(void) const;
	Fixed	y(void) const;


};
