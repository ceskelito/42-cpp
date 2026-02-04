#include "Point.class.hpp"

Point::Point(void) : 
	_x(0),
	_y(0) {};

Point::Point(const float x, const float y) :
	_x(x),
	_y(y) {};

Point::Point(Point &other) : 
	_x(other._x),
	_y(other._y) {};

Point::~Point(void) {};

Point	&Point::operator=(Point &other) {
	if (this != &other) {
		_x = other._x;
		_y = other._y;
	}
	return (*this);
};
