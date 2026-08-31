#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <cassert>

#include "Range.hpp"
#include "Element.hpp"

// Templated implementation of the Ford-Johnson (merge-insertion) algorithm.
// C++98-compatible. This implementation keeps the original algorithm's logic
// but generalizes container and value types. Comparison counting is performed
// per-instance and can be read from the engine after running.

template < template <typename, typename> class Cont, typename T, typename Alloc >
class PmergeMeEngine {
public:
    typedef Cont<T, Alloc> Container;
    typedef typename Container::iterator Iterator;
    typedef Element<Iterator> Elem;
    typedef Cont<Elem, std::allocator<Elem> > ElementList;

    unsigned long comparisons;

    PmergeMeEngine() : comparisons(0) {}

    Cont<T, Alloc> run(Container sequence) {
        unsigned int elementSize = divideIntoAndSortPairs(sequence);

        // Debug: print the sequence after dividing/sorting
        std::cout << "Diveded And Sorted : ";
        debugPrint(sequence);
        std::cout << std::endl;

        initializeMainAndPend(sequence, elementSize);
        return sequence;
    }

private:
    static unsigned int getJacobsthalNumber(unsigned int index) {
        return ( (std::pow(2, index+1) + std::pow(-1, index)) / 3 );
    }

    // Generic debug printer for any container of printable elements
    template <typename C>
    static void debugPrint(const C &c) {
        for (typename C::const_iterator it = c.begin(); it != c.end(); ++it)
            std::cout << *it << " ";
    }

    inline bool cmpGreater(const T &a, const T &b) { ++comparisons; return a > b; }
    inline bool cmpLessEqual(const T &a, const T &b) { ++comparisons; return a <= b; }

    void appendRange(Container &s, Range<Iterator> r) {
        s.insert(s.end(), r.first, r.last);
    }

    int divideIntoAndSortPairs(Container &sequence, unsigned int elementSize = 1) {
        unsigned int pairSize = 2 * elementSize;

        if (pairSize > sequence.size())
            return (elementSize == 1) ? 1 : elementSize / 2;

        for (Iterator it = sequence.begin(); pairSize <= std::distance(it, sequence.end()); it += pairSize) {

            Range<Iterator> firstElement = makeRange(it, it + elementSize - 1);
            Range<Iterator> secondElement = makeRange(it + elementSize, it + pairSize - 1);

            if (cmpGreater(*firstElement.last, *secondElement.last))
                std::swap_ranges(firstElement.first, secondElement.first, secondElement.first);
        }
        return divideIntoAndSortPairs(sequence, 2 * elementSize);
    }

    void insertPendIntoMain(ElementList &main, ElementList &pend) {

        unsigned int jacoIndex = 2; // index 2 return the number 3
        while (!pend.empty())
        {
            typename ElementList::iterator elementToInsert;
            typename ElementList::iterator insertPosition;
            bool insertedThisRound = false;
            unsigned int currentIndex = getJacobsthalNumber(jacoIndex);
            unsigned int previousIndex = (jacoIndex > 1) ? getJacobsthalNumber(jacoIndex - 1) : 1;

            for (unsigned int index = currentIndex; index > previousIndex; --index)
            {
                // Find the right pend element
                for (elementToInsert = pend.begin(); elementToInsert != pend.end(); ++elementToInsert)
                    if (elementToInsert->index == index)
                        break;
                if (elementToInsert == pend.end())
                    break; // nothing found for this index

                for (insertPosition = main.begin(); insertPosition != main.end(); ++insertPosition)
                    if (insertPosition->label == 'a' && insertPosition->index == elementToInsert->index)
                        break;
                if (insertPosition == main.end())
                    break; // position not found

                while (insertPosition != main.begin()) {
                    typename ElementList::iterator previousPosition = insertPosition - 1;
                    if (cmpLessEqual(previousPosition->value, elementToInsert->value))
                        break;
                    insertPosition = previousPosition;
                }
                main.insert(insertPosition, *elementToInsert);
                pend.erase(elementToInsert);
                insertedThisRound = true;
            }

            if (!insertedThisRound)
            {
                while (!pend.empty())
                {
                    elementToInsert = pend.end() - 1;

                    for (insertPosition = main.begin(); insertPosition != main.end(); ++insertPosition)
                        if (insertPosition->label == 'a' && insertPosition->index == elementToInsert->index)
                            break;

                    while (insertPosition != main.begin()) {
                        typename ElementList::iterator previousPosition = insertPosition - 1;
                        if (cmpLessEqual(previousPosition->value, elementToInsert->value))
                            break;
                        insertPosition = previousPosition;
                    }
                    main.insert(insertPosition, *elementToInsert);
                    pend.erase(elementToInsert);
                }
                break;
            }
            ++jacoIndex;
        }
        pend.clear();
    }

    void initializeMainAndPend(Container &sequence, unsigned int elementSize) {
        Container non;
        ElementList main, pend;

        int nElements = sequence.size() / elementSize;
        for (int i = 0; i < nElements; i++)
        {
            Iterator elementStartIt = sequence.begin() + i * elementSize;
            Iterator elementEndIt = elementStartIt + elementSize;
            Range<Iterator> elementRange = makeRange(elementStartIt, elementEndIt);
            int elementIndex = (i / 2) + 1;
            char elementLabel = (i % 2 == 0) ? 'b' : 'a';
            Elem element (elementRange, elementLabel, elementIndex);

            if (elementLabel == 'a' || elementIndex == 1)
                main.push_back(element); // Every a's and b1 goes in main
            else
                pend.push_back(element); // Other b's goes in pend
        }

        // Handle remaining units that can't form an element
        unsigned int processedUnits = (sequence.size() / elementSize) * elementSize;
        for (Iterator it = sequence.begin() + processedUnits; it != sequence.end(); it++) {
            non.insert(non.end(), *it);
        }

        // Debug output
        std::cout << "SIZE: " << elementSize << std::endl;

        std::cout << "main : ";
        Container tmpMain;
        for (typename ElementList::iterator it = main.begin(); it != main.end(); it++)
            appendRange(tmpMain, it->range);
        debugPrint(tmpMain);
        std::cout << std::endl;

        std::cout << "pend : ";
        Container tmpPend;
        for (typename ElementList::iterator it = pend.begin(); it != pend.end(); it++)
            appendRange(tmpPend, it->range);
        debugPrint(tmpPend);
        std::cout << std::endl;

        std::cout << "nonp : ";
        debugPrint(non);
        std::cout << std::endl << std::endl;

        insertPendIntoMain(main, pend);

        Container reordered;
        for (typename ElementList::iterator it = main.begin(); it != main.end(); it++)
            appendRange(reordered, it->range);
        reordered.insert(reordered.end(), non.begin(), non.end());
        sequence.swap(reordered);

        if (elementSize > 1)
            initializeMainAndPend(sequence, elementSize / 2);
    }
};

template < template <typename, typename> class Cont, typename T, typename Alloc >
Cont<T, Alloc> ford_johnson_template(Cont<T, Alloc> sequence) {
    PmergeMeEngine<Cont, T, Alloc> engine;
    Cont<T, Alloc> result = engine.run(sequence);
    // Optionally the caller can inspect engine.comparisons if needed; we return only the sequence.
    (void)engine; // silence unused variable warning when not used
    return result;
}

// Variant that returns the number of comparisons via an output parameter.
template < template <typename, typename> class Cont, typename T, typename Alloc >
Cont<T, Alloc> ford_johnson_with_count_template(Cont<T, Alloc> sequence, unsigned long &outComparisons) {
    PmergeMeEngine<Cont, T, Alloc> engine;
    Cont<T, Alloc> result = engine.run(sequence);
    outComparisons = engine.comparisons;
    return result;
}
