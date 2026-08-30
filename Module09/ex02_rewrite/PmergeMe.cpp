#include <deque>
#include <cmath>
#include <algorithm>
#include "PmergeMe_impl.hpp"
#include "PmergeMe.hpp"
#include <deque>

// Non-templated wrapper kept for existing API compatibility.
std::deque<int> ford_johnson(std::deque<int> sequence) {
	return ford_johnson_template< std::deque, int, std::allocator<int> >(sequence);
}

// Wrapper that also returns the number of comparisons via an output parameter.
std::deque<int> ford_johnson_with_count(std::deque<int> sequence, unsigned long &outComparisons) {
	return ford_johnson_with_count_template< std::deque, int, std::allocator<int> >(sequence, outComparisons);
}
unsigned int	getJacobsthalNumber(unsigned int index) {

	return ( (std::pow(2, index+1) + std::pow(-1, index)) / 3 );

}
