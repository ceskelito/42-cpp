#include "Span.class.hpp"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits.h>

Span::Span(void): _size(0), _v() {};
Span::Span(unsigned const n): _size(n), _v() {};
Span::Span(Span const & other): _size(other._size), _v(other._v) {};

Span& Span::operator=( Span const& other )
{
	if (this != &other) {
		_size = other._size;
		_v = other._v;
	}
	return *this;
}

void	Span::addNumber(unsigned const & n) {

	if (_v.size() == _size)
		throw std::length_error("Span is already full");

	_v.push_back(n);
	std::sort(_v.begin(), _v.end());
}

unsigned	Span::shortestSpan() const {
	
	unsigned smallest = UINT_MAX;
	unsigned curr = 0;

	if (_v.size() <= 1)
		throw std::length_error("Span does not contain enough objects");

	for (int i = _v.size() - 1; i > 0; i--)
	{
		curr = _v[i] - _v[i - 1];
		if (curr < smallest)
			smallest = curr;
	}

	return smallest;
};

unsigned	Span::longestSpan() const {

	if (_v.size() <= 1)
		throw std::length_error("Span does not contain enough objects");

	return _v[_v.size() - 1] - _v[0];
}
