#pragma once

#include "Range.hpp"

template <typename Iterator>
Iterator previousIterator(Iterator it) {
	--it;
	return it;
}

template <typename Iterator>
struct Element {
	Range<Iterator>	range;
	char			label;
	unsigned int	index;
	// The element's value is the value_type from the iterator's traits
	typedef typename std::iterator_traits<Iterator>::value_type value_type;
	value_type	value;

	Element(Range<Iterator> r, char l, unsigned int i)
		: range(r), label(l), index(i), value(*previousIterator(range.last)) {};
};
