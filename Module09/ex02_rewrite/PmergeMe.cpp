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

	for (unsigned int i = elementSize; i > 0; i--) {

		unsigned int	pairSize = 2 * i;

		for (dq::iterator it = sequence.begin(); std::distance(it, sequence.end()) >= pairSize; it += pairSize) {

			Range<dq::iterator>	elementA = makeRange(it, it + elementSize - 1);
			Range<dq::iterator>	elementB = makeRange(it + elementSize, it + pairSize - 1);

			// Initialize main and pending
			if (it == sequence.begin()) // Only b1 had to be insert
				appendRange(main, elementB);
			else
				appendRange(pend, elementB);
			appendRange(main, elementA);

			if (!pend.empty()){
				// logic to insert elements in main
			}
			// How to rewrite the original sequence???
			//
			// My elements are ranges of iterators, so i can
			// use swap_ranges on the elements, ez.
		}
	}

}

static int dividePairsAndSort(dq &sequence, unsigned int elementSize = 1) {

	if (2 * elementSize > sequence.size())
		return elementSize;
		// return sequence;

	unsigned int pairSize = 2 * elementSize;

	for (dq::iterator it = sequence.begin(); std::distance(it, sequence.end()) >= pairSize; it += pairSize) {

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
	

