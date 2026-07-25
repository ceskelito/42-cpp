#include <deque>
#include <cmath>
#include <algorithm>
#include "Range.hpp"

typedef std::deque<int> dq;

unsigned int	getJacobsthalNumber(unsigned int index) {
	return ( (std::pow(2, index+1) + std::pow(-1, index)) / 3 );
}

void	appendRange(dq &s, Range<dq::iterator> r) {
	s.insert(s.end(), r.first, r.last + 1);
}

// void	initializeAndInsertWrong(dq &sequence, unsigned int elementSize)
// {
// 	dq				main, pend;
//
// 	// STEP 1: Divide main and pend into groups
// 	unsigned int	pairSize = 2 * elementSize;
// 	for (dq::iterator it = sequence.begin(); std::distance(it, sequence.end()) >= pairSize; it += pairSize) {
//
// 		Range<dq::iterator>	elementA = makeRange(it, it + elementSize - 1);
// 		Range<dq::iterator>	elementB = makeRange(it + elementSize, it + pairSize - 1);
//
// 		if (it == sequence.begin()) 
// 			appendRange(main, elementB);
// 		else
// 			appendRange(pend, elementB);
//
// 		appendRange(main, elementA);
// 	}
//
// 	// Handle remaining elements
// 	unsigned int processed_elements = (sequence.size() / pairSize) * pairSize;
// 	for (dq::iterator it = sequence.begin() + processed_elements; it != sequence.end(); it++) {
// 		main.insert(main.end(), *it);
// 	}
//
// 	// STEP 2: Insert pend elements into main using Jacobsthal sequence
// 	unsigned int jacobsthal_index = 1;
// 	unsigned int pend_index = 0;
//
// 	std::sort(main.begin(), main.end());
//
// 	while (pend_index < pend.size()) {
// 		unsigned int jacobsthal_num = getJacobsthalNumber(jacobsthal_index);
// 		unsigned int limit = std::min(jacobsthal_num, (unsigned int)pend.size());
//
// 		for (unsigned int i = limit; i > pend_index && pend_index < pend.size(); i--) {
// 			dq::iterator pos = std::lower_bound(main.begin(), main.end(), pend[pend_index]);
// 			main.insert(pos, pend[pend_index]);
// 			pend_index++;
// 		}
//
// 		jacobsthal_index++;
// 	}
//
// 	// STEP 3: Copy sorted main back to sequence
// 	sequence.clear();
// 	if (!main.empty())
// 		appendRange(sequence, makeRange(main.begin(), main.end() - 1));
//
// 	// STEP 4: Recurse with next group size
// 	if (elementSize > 1) {
// 		initializeAndInsertWrong(sequence, 2 * elementSize);
// 	}
// }

void	initializeAndInsert(dq &sequence, unsigned int elementSize)
{
	dq				main, pend, nonPartecipating;
	unsigned int	pairSize = 2 * elementSize;

	// STEP 1: Sort elements in main and pend groups
	for (dq::iterator it = sequence.begin(); pairSize <= std::distance(it, sequence.end()); it += pairSize) {
		
		Range<dq::iterator>	elementA = makeRange(it, it + elementSize - 1);
		Range<dq::iterator>	elementB = makeRange(it + elementSize, it + pairSize - 1);
		
		if (it == sequence.begin()) 
			appendRange(main, elementB); // Only b1 goes in main
		else
			appendRange(pend, elementB); // Other b's goes in pens

		appendRange(main, elementA); // Every a goes in main
	}

	// Handle remaining elements
	unsigned int processedElements = (sequence.size() / pairSize) * pairSize;
	for (dq::iterator it = sequence.begin() + processedElements; it != sequence.end(); it++) {
		nonPartecipating.insert(nonPartecipating.end(), *it);
	}

	// STEP 2: Insert pend elements into main using Jacobsthal sequence
	unsigned int jacoIndex = 1;

	while (pend.size()) {
		unsigned int jacoNum = getJacobsthalNumber(jacoIndex);
		unsigned int prevJacoNum = (jacoIndex > 1) ? getJacobsthalNumber(jacoIndex - 1) : 0;

		// Insert elements B from jacoNum down to prevJacoNum+1, backwards
		for (unsigned int b_index = jacoNum; b_index > prevJacoNum; b_index--) {
			// Calculate start and end indices of B[b_index] in pend array
			unsigned int start_idx = (b_index - 1) * elementSize;
			unsigned int end_idx = b_index * elementSize - 1;

			// Check boundaries
			if (end_idx >= pend.size() - 1)
				continue;

			// Create Range for this B element
			Range<dq::iterator> elementB = makeRange(pend.begin() + start_idx,
													   pend.begin() + end_idx);
			dq::iterator pos = main.begin() + end_idx;
			while (*pos > *elementB.last)
				pos -= elementSize;

			// Insert the entire range into main (and removes it from pend)
			main.insert(pos, elementB.first, elementB.last + 1);
			pend.erase(elementB.first, elementB.last );
		}

		jacoIndex++;
	}

	// STEP 3: Copy sorted main + nonPartecipating back to sequence
	sequence.clear();
	sequence.insert(sequence.end(), main.begin(), main.end() - 1);
	sequence.insert(sequence.end(), nonPartecipating.begin(), nonPartecipating.end() - 1);
	
	if (elementSize != 1)
		initializeAndInsert(sequence, elementSize / 2);
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
	dividePairsAndSort(sequence);
	initializeAndInsert(sequence, 1);
	return sequence;
}


