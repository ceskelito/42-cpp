#include <deque>
#include <cmath>
#include "Range.hpp"

// Source: STEP 1 of https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91

typedef std::deque<int> dq;

unsigned int	getJacobsthalNumber(unsigned int n) {
	return ( (std::pow(2, n+1) + std::pow(-1, n)) / 3 );
}

// void	insertElement(dq &main, Range<dq::iterator> element) {
//
// }

void	appendRange(dq &s, Range<dq::iterator> r) {
	s.insert(s.end(), r.first, r.last);
}

void	initializeAndInsert(dq &sequence, unsigned int elementSize)
{
	dq				main, pend;

	// STEP 1: Divide main and pend
	unsigned int	pairSize = 2 * elementSize;
	for (dq::iterator it = sequence.begin(); std::distance(it, sequence.end()) >= pairSize; it += pairSize) {
		
		Range<dq::iterator>	elementA = makeRange(it, it + elementSize - 1);
		Range<dq::iterator>	elementB = makeRange(it + elementSize, it + pairSize - 1);
		
		if (it == sequence.begin()) 
			appendRange(main, elementB); // Only b1 goes in main
		else
			appendRange(pend, elementB); // Other b's go in pending

		appendRange(main, elementA);	// Every a goes in main
	}

	// STEP 2

}

static int dividePairsAndSort(dq &sequence, unsigned int elementSize = 1) {

	unsigned int pairSize = 2 * elementSize;

	if (pairSize > sequence.size())
		return elementSize;

	for (dq::iterator it = sequence.begin(); pairSize <= std::distance(it, sequence.end()); it += pairSize) {

		Range<dq::iterator>	elementA = makeRange(it, it + elementSize - 1);
		Range<dq::iterator>	elementB = makeRange(it + elementSize, it + pairSize - 1);

		if (*elementA.last > *elementB.last)
			std::swap_ranges(elementA.first, elementB.first, elementB.first);
	}
	return dividePairsAndSort(sequence, 2 * elementSize);
}

std::deque<int> ford_johnson(std::deque<int> sequence) {
	unsigned int elementSize;

	elementSize = dividePairsAndSort(sequence);
	initializeAndInsert(sequence, elementSize);
	return sequence;
}
	

