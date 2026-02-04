#pragma once

#include "Fixed.class.hpp"

class Point {

	private:

	Fixed	_x;
	Fixed	_y;

	public:

	// Constructors / Destructor
	Point(void);
	Point(const float x, const float y);
	Point(Point &other);
	~Point(void);

	// Operators overload
	Point	&operator=(Point &other);



};

bool	bsp( Point const a, Point const b, Point const c, Point const point);
