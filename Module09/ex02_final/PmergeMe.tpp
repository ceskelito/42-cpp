#pragma once

#include "PmergeMe.hpp"

#include <iterator>

template <typename It> bool PmergeMe::_comp(It lv, It rv, int &nbr_of_comparisons)
{
	nbr_of_comparisons++;
	return *lv < *rv;
}

template <typename It> It PmergeMe::_next(It it, int steps)
{
	std::advance(it, steps);
	return it;
}

template <typename It> void	PmergeMe::_swap_elems(It first_elem, int element_size)
{

	It start = _next(first_elem, -element_size + 1);
	It end = _next(first_elem, 1);

	while (start != end)
	{
		std::iter_swap(start, _next(start, element_size));
		start++;
	}
}

template <typename T>
typename T::iterator PmergeMe::_element_begin(T &container, int element_index, int element_size)
{
	return _next(container.begin(), element_index * element_size);
}

template <typename T>
typename T::iterator PmergeMe::_element_last(T &container, int element_index, int element_size)
{
	return _next(container.begin(), (element_index + 1) * element_size - 1);
}

template <typename T>
typename T::iterator PmergeMe::_element_end(T &container, int element_index, int element_size)
{
	return _next(container.begin(), (element_index + 1) * element_size);
}

template <typename T>
int PmergeMe::_upper_bound_element_index(T &main, int bound_idx, T &pend, int source_idx, int element_size, int &nbr_of_comparisons)
{
	int lo = 0;
	int hi = bound_idx;
	while (lo < hi)
	{
		int mid = lo + (hi - lo) / 2;
		if (_comp(_element_last(pend, source_idx, element_size),
				  _element_last(main, mid, element_size), nbr_of_comparisons))
			hi = mid;
		else
			lo = mid + 1;
	}
	return lo;
}

template <typename T>
void PmergeMe::_append_element(T &dst, T &src, int source_idx, int element_size)
{
	dst.insert(dst.end(), _element_begin(src, source_idx, element_size),
			   _element_end(src, source_idx, element_size));
}

template <typename T>
void PmergeMe::_insert_element_before(T &dst, int bound_idx, T &src, int source_idx, int element_size)
{
	dst.insert(_element_begin(dst, bound_idx, element_size),
			   _element_begin(src, source_idx, element_size),
			   _element_end(src, source_idx, element_size));
}

template <typename T>
void PmergeMe::_erase_element(T &container, int element_index, int element_size)
{
	container.erase(_element_begin(container, element_index, element_size),
				_element_end(container, element_index, element_size));
}

template <typename T> void PmergeMe::_ford_johnson_merge_insertion_sort(T &sequence, int element_size, int &nbr_of_comparisons)
{

	typedef typename T::iterator Iterator;

	int	nbr_of_elems = sequence.size() / element_size;

	if (nbr_of_elems < 2)
		return ;

    /* STEP 1 - Division in pairs, sorting of pairs */

	bool is_odd = nbr_of_elems % 2;

	Iterator start = sequence.begin();
	Iterator last = _next(sequence.begin(), (element_size * nbr_of_elems)); // Iterator to the start of last element
	Iterator end = _next(last, -(is_odd * element_size)); // Iterator to the start of the last element that can be paired with the next to it

	int pair_size = element_size * 2;
	for (Iterator it = start ; it != end; std::advance(it, pair_size))
	{
		Iterator this_elem = _next(it, element_size - 1);
		Iterator next_elem = _next(it, pair_size - 1);

		if (_comp(next_elem, this_elem, nbr_of_comparisons))
			_swap_elems(this_elem, element_size);
	}

	_ford_johnson_merge_insertion_sort(sequence, element_size * 2, nbr_of_comparisons);

    /* STEP 2 - Creation of Main and Pend chains */

	T main, pend, non;

    // Insert the first 2 elements (b1 and a1) in the main chain
	main.insert(main.end(), sequence.begin(), _next(sequence.begin(), element_size * 2));
    // Insert every other b's in pend and a's in main
	for (int element_index = 2; element_index < nbr_of_elems; element_index += 2)
	{
		_append_element(pend, sequence, element_index, element_size);
		if (element_index + 1 < nbr_of_elems)
			_append_element(main, sequence, element_index + 1, element_size);
	}
    // Number that can not form even a single element are stored separately as non-partecipating numbers
    // Those number will be added at the end of the new sequence at the end of step 3
	if (last != sequence.end())
	{
		non.insert(non.end(), last, sequence.end());
	}

    /* STEP 3 - Insertion of Pend into Main*/

    // Now we will insert element from the pend to main following the jacobsthal sequence for choosing the index to insert
    // From the current jacobsthal insert the corresponding indexed element with binary insertion,
    // then we'll descend until we encounter the previus jacobsthal index. At this point go to the next jacobsthal.
    //
    // When the number of elemets in the range (curr_jaco - prev_jaco] exceed the elements in the pend, we'll insert all the
    // remaining elements from the end of pend in descending order, always binary searching the bound in the main.

	int nbr_main_elements = static_cast<int>(main.size() / element_size);
	int nbr_pend_elements = static_cast<int>(pend.size() / element_size);

	int	prev_jacobsthal = _jacobsthal_number(1);
	int	inserted_numbers = 0;
	for (int k = 2 ;; k++)
	{
		int curr_jacobsthal = _jacobsthal_number(k);
		int jacobsthal_diff = curr_jacobsthal - prev_jacobsthal;
		int offset = 0;
		if (jacobsthal_diff > nbr_pend_elements) {
			break;
		}
		int nbr_of_times = jacobsthal_diff;
		int pend_index = jacobsthal_diff - 1;
		int bound_index = curr_jacobsthal + inserted_numbers;
		while (nbr_of_times)
		{
			int source_element = pend_index;
			int search_end = bound_index - offset;
			if (search_end > nbr_main_elements)
				search_end = nbr_main_elements;
			int insert_pos = _upper_bound_element_index(main, search_end, pend, source_element, element_size, nbr_of_comparisons);
			_insert_element_before(main, insert_pos, pend, source_element, element_size);
			_erase_element(pend, source_element, element_size);
			nbr_of_times--;
			nbr_main_elements++;
			nbr_pend_elements--;
			pend_index--;
			offset += insert_pos == bound_index;
		}
		prev_jacobsthal = curr_jacobsthal;
		inserted_numbers += jacobsthal_diff;
	}

	while (nbr_pend_elements > 0)
    {
    	int source_element = nbr_pend_elements - 1;
		int search_end = nbr_main_elements;
		int insert_pos = _upper_bound_element_index(main, search_end, pend, source_element, element_size, nbr_of_comparisons);
		_insert_element_before(main, insert_pos, pend, source_element, element_size);
		_erase_element(pend, source_element, element_size);
		nbr_main_elements++;
		nbr_pend_elements--;
    }

    // Recreating the whole sequence with ordered main and non-partecipating numbers
	sequence.clear();
	sequence.insert(sequence.end(), main.begin(), main.end());
	sequence.insert(sequence.end(), non.begin(), non.end());

}

template <typename T> int PmergeMe::sort(T &sequence)
{
    int nbr_of_comparisons = 0;

    _ford_johnson_merge_insertion_sort(sequence, 1, nbr_of_comparisons);

    return nbr_of_comparisons;
}
