#include <deque>
#include <cmath>
#include <algorithm>
#include "Range.hpp"
#include "debugUtils.hpp"

typedef std::deque<int> dq;

unsigned int	getJacobsthalNumber(unsigned int index) {
	return ( (std::pow(2, index+1) + std::pow(-1, index)) / 3 );
}

void	appendRange(dq &s, Range<dq::iterator> r) {
	s.insert(s.end(), r.first, r.last + 1);
}

void	initializeAndInsert(dq &sequence, unsigned int elementSize)
{
	dq				main, pend, non;
	unsigned int	pairSize = 2 * elementSize;

	std::cout << std::endl << "SIZE: " << elementSize << std::endl;
	// STEP 1: Sort elements in main and pend groups
	for (dq::iterator it = sequence.begin(); pairSize <= std::distance(it, sequence.end()); it += pairSize) {
		
		Range<dq::iterator>	elementA = makeRange(it, it + elementSize - 1);
		Range<dq::iterator>	elementB = makeRange(it + elementSize, it + pairSize - 1);
		
		if (it == sequence.begin()) 
			appendRange(main, elementB); // Only b1 goes in main
		else
			appendRange(pend, elementB); // Other b's goes in pend

		std::cout << std::endl << "A: " << *elementA.last;
		std::cout << std::endl << "B: " << *elementB.last;
		std::cout << std::endl;

		appendRange(main, elementA); // Every a goes in main
	}

	// DEBUG
	std::cout << "main: ";
	debug::printDeque(main, elementSize);
	std::cout << std::endl;
	std::cout << "pend: ";
	debug::printDeque(pend, elementSize);
	std::cout << std::endl;

	// Handle remaining elements
	unsigned int processedElements = (sequence.size() / pairSize) * pairSize;
	for (dq::iterator it = sequence.begin() + processedElements; it != sequence.end(); it++) {
		non.insert(non.end(), *it);
	}
	std::cout << "non: ";
	debug::printDeque(non);

	// return; // DEBUG
	

	std::cout << std::endl << "PEND SIZE: " << pend.size() << std::endl;
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
	sequence.insert(sequence.end(), main.begin(), main.end());
	sequence.insert(sequence.end(), non.begin(), non.end());
	
	std::cout << "PRE RECURSION: ";
	debug::printDeque(sequence);
	std::cout << std::endl;

	if (elementSize != 1)
		initializeAndInsert(sequence, elementSize / 2);
}

/**
 * @param sequence - The original sequence
 * @param elementSize - The initial size of the element
 *
 * Divide the sequence in elements of size elementSize, doubled on every recursion;
 * puts the smaller element of each pair before the bigger element.
 *
 * An element is a range of units in the sequence.
 * The value of the element is determined by the last unit in the element.
 *
 * Break the recursion when the size of the sequence is smaller then the size of a pair.
 *
 * Return value: The latest possible size of the elements
 * 
 * */
static int divideIntoAndSortPairs(dq &sequence, unsigned int elementSize = 1) {

	unsigned int pairSize = 2 * elementSize;

	if (pairSize > sequence.size())
		return elementSize / 2;

	for (dq::iterator it = sequence.begin(); pairSize <= std::distance(it, sequence.end()); it += pairSize) {

		Range<dq::iterator>	firstElement = makeRange(it, it + elementSize - 1);
		Range<dq::iterator>	secondElement = makeRange(it + elementSize, it + pairSize - 1);

		if (*firstElement.last > *secondElement.last)
			std::swap_ranges(firstElement.first, secondElement.first, secondElement.first);
	}
	return divideIntoAndSortPairs(sequence, 2 * elementSize);
}

static void insertPendIntoMain(dq &main, dq &pend, unsigned int elementSize);
static void initializeMainAndPend(dq &sequence, unsigned int elementSize) {
	
	dq main, pend, non;

	unsigned int	pairSize = 2 * elementSize;

	// STEP 2: Sort elements in main and pend groups
	for (dq::iterator it = sequence.begin(); pairSize <= std::distance(it, sequence.end()); it += pairSize)
	{
		Range<dq::iterator>	elementB = makeRange(it, it + elementSize - 1);
		Range<dq::iterator>	elementA = makeRange(it + elementSize, it + pairSize - 1);
		
		if (it == sequence.begin()) 
			appendRange(main, elementB); // Only b1 goes in main
		else
			appendRange(pend, elementB); // Other b's goes in pend
		appendRange(main, elementA); // Every a goes in main
	}

	// Handle remaining elements
	unsigned int processedElements = (sequence.size() / pairSize) * pairSize;
	for (dq::iterator it = sequence.begin() + processedElements; it != sequence.end(); it++) {
		non.insert(non.end(), *it);
	}

	// DEBUG
	std::cout << std::endl << "SIZE: " << elementSize << std::endl;
	std::cout << "main: ";
	debug::printDeque(main, elementSize);
	std::cout << std::endl;
	std::cout << "pend: ";
	debug::printDeque(pend, elementSize);
	std::cout << std::endl;
	std::cout << "non: ";
	debug::printDeque(non);
	// END DEBUG

	insertPendIntoMain(main, pend, elementSize);

	sequence.clear();
	sequence.insert(sequence.end(), main.begin(), main.end());
	sequence.insert(sequence.end(), non.begin(), non.end());

	// return; // DEBUG

	if (elementSize > 1)
		initializeMainAndPend(sequence, elementSize / 2);
}

static Range<dq::iterator> getElementAtIndex(dq &sequence, unsigned int index, unsigned int elementSize) {
	if (elementSize == 0 || sequence.empty())
		return makeRange(sequence.end(), sequence.end());

	const unsigned int elementCount = sequence.size() / elementSize;
	if (index >= elementCount)
		return makeRange(sequence.end(), sequence.end());

	dq::iterator first = sequence.begin() + (index * elementSize);
	dq::iterator last = first + elementSize - 1;
	return makeRange(first, last);
}

static void insertPendIntoMain(dq &main, dq &pend, unsigned int elementSize) {

	if (elementSize == 0 || pend.empty())
		return;

	struct Block {
		Range<dq::iterator> range;
		unsigned int label;

		Block(Range<dq::iterator> r, unsigned int l) : range(r), label(l) {}
	};

	std::deque<Block> pendBlocks;
	for (dq::iterator it = pend.begin();
		 std::distance(it, pend.end()) >= static_cast<int>(elementSize);
		 it += elementSize) {
		pendBlocks.push_back(Block(makeRange(it, it + elementSize - 1),
						   static_cast<unsigned int>(pendBlocks.size() + 2)));
	}

	unsigned int jacoIndex = 1;
	while (!pendBlocks.empty())
	{
		unsigned int currentLabel = getJacobsthalNumber(jacoIndex) + 1;
		unsigned int previousLabel = (jacoIndex > 1) ? getJacobsthalNumber(jacoIndex - 1) + 1 : 1;

		for (unsigned int label = currentLabel; label > previousLabel; --label)
		{
			std::deque<Block>::iterator block;
			for (block = pendBlocks.begin(); block != pendBlocks.end(); ++block)
			{
				if (block->label == label)
					break;
			}
				dq::iterator insertPosition = main.begin() + elementSize * (currentLabel - 1) - 1;

				while (*insertPosition > *block->range.last)
					insertPosition -= elementSize;
				main.insert(insertPosition - elementSize, block->range.first, block->range.last + 1);
				pendBlocks.erase(block);
				break;
		}

		++jacoIndex;
	}

	pend.clear();
};

std::deque<int> ford_johnson(std::deque<int> sequence) {
	unsigned int elementSize = divideIntoAndSortPairs(sequence);

	// DEBUG
	std::cout << "Diveded And Sorted : ";
	debug::printDeque(sequence);
	std::cout << std::endl;

	initializeMainAndPend(sequence, elementSize);
	return sequence;
}


