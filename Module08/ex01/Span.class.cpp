#include "Span.class.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <stdexcept>

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

// Add single element and sort
void	Span::addNumber(unsigned const & n) {

	if (_v.size() == _size)
		throw std::length_error("Span is already full");

	_v.push_back(n);
	std::sort(_v.begin(), _v.end());
}

// Add range of elements and sort
void	Span::addRange(vec_iter & begin, vec_iter & end) {

	if (static_cast<long unsigned>(std::distance(begin, end)) > _size - _v.size())
		throw std::length_error("Span cannot contain this range");

	_v.insert(_v.end(), begin, end);
	std::sort(_v.begin(), _v.end());
}

// Add multiple copies of a value and sort
void	Span::addRange(unsigned const & count, int const & value) {

	if (count > _size - _v.size())
		throw std::length_error("Span cannot contain this range");

	_v.insert(_v.end(), count, value);
	std::sort(_v.begin(), _v.end());
}

// Find smallest span using adjacent differences
unsigned	Span::shortestSpan() const {

	std::vector<int>	diffs(_v.size());

	if (_v.size() <= 1)
		throw std::length_error("Span does not contain enough objects");

	std::adjacent_difference(_v.begin(), _v.end(), diffs.begin());

	return *std::min_element(diffs.begin() + 1, diffs.end());
}

// Find largest span: difference between max and min (possible because vector is sorted)
unsigned	Span::longestSpan() const {

	if (_v.size() <= 1)
		throw std::length_error("Span does not contain enough objects");

	return _v[_v.size() - 1] - _v[0];
}
