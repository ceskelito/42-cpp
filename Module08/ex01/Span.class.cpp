#include "Span.class.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <limits.h>

Span::Span(void): _size(0), _v() {};
Span::Span(unsigned const n): _size(n), _v() {};
Span::Span(Span const & other): _size(other._size), _v(other._v) {};
Span::~Span(void) {};

Span& Span::operator=( Span const& other )
{
	if (this != &other) {
		_size = other._size;
		_v = other._v;
	}
	return *this;
}

// Append the element @n. Then sort _v
void	Span::addNumber(unsigned const & n) {

	if (_v.size() == _size)
		throw std::length_error("Span is already full");

	_v.push_back(n);
	std::sort(_v.begin(), _v.end());
}

// Append to _v the elements in the range between @begin and @end.
// Then sort _v
void	Span::addRange(vec_iter & begin, vec_iter & end) {

	if (static_cast<long unsigned>(std::distance(begin, end)) > _size - _v.size())
		throw std::length_error("Span cannot contain this range");

	_v.insert(_v.end(), begin, end);
	std::sort(_v.begin(), _v.end());
}

// Append to _v @counts num of elements of value @value.
// Then sort _v
void	Span::addRange(unsigned const & count, int const & value) {

	if (count > _size - _v.size())
		throw std::length_error("Span cannot contain this range");

	_v.insert(_v.end(), count, value);
	std::sort(_v.begin(), _v.end());
}

// Obtain the shortestSpan
// First obtain a vector containing the diffs of the adjacent elements in _v,
// then return the min element skipping the first (that correspond at the first element of _v)
unsigned	Span::shortestSpan() const {

	std::vector<int>	diffs(_v.size());

	if (_v.size() <= 1)
		throw std::length_error("Span does not contain enough objects");

	std::adjacent_difference(_v.begin(), _v.end(), diffs.begin());

	return *std::min_element(diffs.begin() + 1, diffs.end());
}

// Since _v is sorted, the longestSpan is the difference
// between the last and first elements of the vector _v
unsigned	Span::longestSpan() const {

	if (_v.size() <= 1)
		throw std::length_error("Span does not contain enough objects");

	return _v[_v.size() - 1] - _v[0];
}
