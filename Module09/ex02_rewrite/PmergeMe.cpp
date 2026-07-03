#include <deque>
#include <utility>

// Source: STEP 1 of https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91

typedef std::deque<int> dq;

static dq dividePairsAndSort(dq sequence, unsigned int elementSize = 1) {

	if (2 * elementSize > sequence.size())
		return sequence;

	unsigned int pairSize = 2 * elementSize;

	for (dq::iterator it = sequence.begin(); std::distance(it, sequence.end()) >= pairSize; it += pairSize) {

		std::pair<dq::iterator, dq::iterator> firstElem = std::make_pair(it, it + elementSize - 1);
		std::pair<dq::iterator, dq::iterator> secondElem = std::make_pair(it + elementSize, it + 2 * elementSize - 1);


		// dq::iterator firstElem_labelA = it + elementSize - 1;
		// dq::iterator secondElem_labelA = it + pairSize - 1;

		if (*firstElem.second > *secondElem.second)
			std::swap_ranges(firstElem.first, secondElem.first, secondElem.first);
	}
	return dividePairsAndSort(sequence, 2 * elementSize);
}

// Interface to avoid erroneous call
dq dividePairsAndSort(dq sequence) {
	return dividePairsAndSort(sequence, 1);
}
	
