#include "Span.class.hpp"
#include <vector>
#include <algorithm>
#include <numeric>
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
	std::sort(_v.cbegin(), _v.cend());
}
void	Span::addRange(std::vector<int>::const_iterator & begin,
						std::vector<int>::const_iterator & end) {
	// implement

}

unsigned	Span::shortestSpan() const {

	std::vector<int>	diffs(_v.size());

	if (_v.size() <= 1)
		throw std::length_error("Span does not contain enough objects");

	std::adjacent_difference(_v.cbegin(), _v.cend(), diffs.begin());

	return diffs[1];
}

unsigned	Span::longestSpan() const {

	if (_v.size() <= 1)
		throw std::length_error("Span does not contain enough objects");

	return _v[_v.size() - 1] - _v[0];
}
