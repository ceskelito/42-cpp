#include "Point.class.hpp"

Point::Point(void) : 
	_x(0),
	_y(0) {};

Point::Point(const float x, const float y) :
	_x(x),
	_y(y) {};

Point::Point(Point const &other) : 
	_x(other._x),
	_y(other._y) {};

Point::~Point(void) {};

// Since _x and _y are const, this operator will do nothing.
Point	&Point::operator=(Point const &other) {
	// if (this != &other) {
	// 	_x = other._x;
	// 	_y = other._y;
	// }
	(void)other;
	return (*this);
};
