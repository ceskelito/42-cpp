#include <deque>

typedef std::deque<int> dq;

dq dividePairsAndSort(dq sequence, unsigned int elementSize = 1) {

	if (elementSize > sequence.size() / 2)
		return sequence;
	
	for (dq::iterator it = sequence.begin(); std::distance(it, sequence.end()) > elementSize; it++) {
		if (*it > *(it + elementSize))
			std::swap_ranges(it, it + elementSize - 1, it + elementSize);
	}
	return dividePairsAndSort(sequence, elementSize + 1);
}
	
