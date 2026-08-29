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
	unsigned int	value;

	Element(Range<Iterator> r, char l, unsigned int i)
		: range(r), label(l), index(i), value(*previousIterator(range.last)) {};
};
