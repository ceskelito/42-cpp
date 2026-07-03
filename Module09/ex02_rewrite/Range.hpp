#pragma once

#include <iterator>

template <typename Iterator>
struct Range {
    Iterator first;
    Iterator last;

    Range(Iterator f, Iterator l) : first(f), last(l) {}

    Iterator begin() const { return first; }
    Iterator end()   const { return last; }

    bool empty() const { return first == last; }
    typename std::iterator_traits<Iterator>::difference_type
		size() const { return std::distance(first, last); }
};

template <typename Iterator>
Range<Iterator> makeRange(Iterator f, Iterator l) {
    return Range<Iterator>(f, l);
}
