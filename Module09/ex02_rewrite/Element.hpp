#pragma once

#include "Range.hpp"

template <typename Iterator>
struct Element {
	Range<Iterator>	range;
	char			label;
	unsigned int	index;

	Element(Range<Iterator> r, char l, unsigned int i): range(r), label(l), index(i) {};
	// Element(Iterator r_f, Iterator r_l, char l, unsigned int i): range(Range<Iterator>(r_f, r_l)), label(l), index(i) {}
};

// template <typename Iterator>
// struct Element: public Range<Iterator> {
// 	char			label;
// 	unsigned int	index;
//
// 	Element(Iterator r_f, Iterator r_l, char l, unsigned int i): Range<Iterator>(r_f, r_l), label(l), index(i) {}
// };
