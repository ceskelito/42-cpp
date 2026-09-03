#pragma once
#include <iterator>
#include <iostream>
#include <vector>
#include <deque>

class PmergeMe {

	private:
		template <typename T>
		static void			 _initalize_main_and_pend(T &sequence, int pair_size, int &comps_counter);

		template <typename T>
		static void			_insert_pend_into_main(T &main, T &pend, int & comps_counter);

		template <typename T>
		static int			_split_into_pairs_and_sort(T &sequence, int &comps_counter, int element_size = 1);

		template <typename It>
		static bool			_comp(It lv, It rv, int &comps_counter);

		template <typename It>
		static It			_next(It it, int steps);

		template <typename It>
		static void			_swap_elems(It first_elem, int element_size);

		template <typename T, typename It>
		static void			_push_elem(T &chain, It elem, int element_size);

		template <typename T>
		static typename T::iterator
							_get_elem_it(T &chain, int index, int element_size);

	public:
		template <typename T>
		static T			ford_johnson_merge_insertion_sort(T sequence, int &comps_counter);
};

template <typename It> bool PmergeMe::_comp(It lv, It rv, int &comps_counter) {
	comps_counter++;
	return *lv < *rv;
}

template <typename It> It PmergeMe::_next(It it, int steps)
{
    std::advance(it, steps);
    return it;
}

template <typename It> void	PmergeMe::_swap_elems(It first_elem, int element_size) {

	It start = _next(first_elem, -element_size + 1);
	It end = _next(first_elem, 1);

	while (start != end)
	{
		std::iter_swap(start, _next(start, element_size));
		start++;
	}
}

template <typename T, typename It> void PmergeMe::_push_elem(T &chain, It elem, int element_size) {

	It start = _next(elem, -element_size + 1);
	It end = _next(elem, 1);

	while (start != end)
	{
		chain.insert(chain.end(), *start);
		start++;
	}

}

template <typename T> typename T::iterator _get_elem_it(T &chain, int index, int element_size) {
	return _next(chain, element_size * index - 1);
}


#include <cmath>
// int	getJacobsthalNumber(int index);
// int	getJacobsthalNumber(int index) {
// 	return ( (std::pow(2, index+1) + std::pow(-1, index)) / 3 );
// }
#define JACO(index) ((std::pow(2, index+1) + std::pow(-1, index)) / 3 )

template <typename T> T	PmergeMe::ford_johnson_merge_insertion_sort(T sequence, int &comps_counter) {

	int	element_size;

	element_size = _split_into_pairs_and_sort(sequence, comps_counter);
	(void) element_size;

	typedef typename T::iterator Iterator;

	/* Init main and pend */
	// _initalize_main_and_pend(sequence, element_size, comps_counter);
	element_size /= 2;
	if (sequence.size() < static_cast<size_t>(2 * element_size)) {
		std::cout << "PIPPA!" << std::endl;
		return sequence;
	}

	T		main, pend, non;

	int		nbr_of_elems = sequence.size() / element_size;
	bool	is_odd = nbr_of_elems % 2;

	_push_elem(main, _next(sequence.begin(), element_size - 1), element_size);		// Push b1 into main
	_push_elem(main, _next(sequence.begin(), 2 * element_size - 1), element_size);	// Push a1 into main

	Iterator start = _next(sequence.begin(), 2 * element_size); // Starting from b2
	Iterator last = _next(sequence.begin(), (element_size * nbr_of_elems));
	Iterator end = _next(last, -(is_odd * element_size));
	
	for (Iterator it = start; it != end; std::advance(it, 2 * element_size)) {

		Iterator	b_elem = _next(it, element_size - 1);
		Iterator	a_elem = _next(it, 2 * element_size - 1);

		_push_elem(pend, b_elem, element_size);
		_push_elem(main, a_elem, element_size);
	}

	if (is_odd)
	{
		_push_elem(pend, _next(end, element_size - 1), element_size);
	}

	while (last != sequence.end())
	{
		non.insert(non.end(), *last);
		last++;
	}

	std::cout << "END STEP 2" << std::endl;

	/* STEP 3 */

	int	prev_jacobsthal = JACO(1);
	int	inserted_numbers = 0;
	for (int k = 2 ;; k++)
	{
		int curr_jacobsthal = JACO(k);
		int jacobsthal_diff = curr_jacobsthal - prev_jacobsthal;
		if (jacobsthal_diff > static_cast<int> (pend.size() / element_size)) {
			std::cout << "PIPPA 2 !" << std::endl;
			std::cout << jacobsthal_diff << " > " << pend.size() / element_size << std::endl;
			break;
		}
		int	nbr_of_times = jacobsthal_diff;
		Iterator bound_it = _next(main.begin(), (inserted_numbers + curr_jacobsthal) * element_size);
		Iterator pend_it = _next(pend.begin(), (jacobsthal_diff * element_size) - 1);
		while (nbr_of_times)
		{
			std::cout << "WHIILEE" << std::endl;
			Iterator idx;
			for (idx = bound_it; !_comp(pend_it, _next(idx, -1), comps_counter); _next(idx, -element_size));
			main.insert(idx, *pend_it);
			--nbr_of_times;
			pend_it = pend.erase(pend_it);
			std::advance(pend_it, -1);
		}
		prev_jacobsthal = curr_jacobsthal;
		inserted_numbers += jacobsthal_diff;
	}
	
	// Now i will add the remaining numbers in descending order


	return sequence;
}

template <typename T> int PmergeMe::_split_into_pairs_and_sort(T &sequence, int &comps_counter, int element_size) {

	typedef typename T::iterator Iterator;

	int	nbr_of_elems = sequence.size() / element_size;

	if (nbr_of_elems < 2)
		return element_size;

	bool is_odd = nbr_of_elems % 2;

	Iterator start = sequence.begin();
	Iterator last = _next(sequence.begin(), (element_size * nbr_of_elems));
	Iterator end = _next(last, -(is_odd * element_size));

	int pair_size = element_size * 2;
	for (Iterator it = start ; it != end; std::advance(it, pair_size)) {

		Iterator this_elem = _next(it, element_size - 1);
		Iterator next_elem = _next(it, pair_size - 1);

		if (_comp(next_elem, this_elem, comps_counter))
			_swap_elems(this_elem, element_size);
	}
	return _split_into_pairs_and_sort(sequence, comps_counter, element_size * 2);
}


template <typename T> void PmergeMe::_initalize_main_and_pend(T &sequence, int element_size, int &comps_counter) {

	typedef typename T::iterator Iterator;

	if (sequence.size() < static_cast<size_t>(2 * element_size))
		return;

	T		main, pend, non;

	int		nbr_of_elems = sequence.size() / element_size;
	bool	is_odd = nbr_of_elems % 2;

	_push_elem(main, _next(sequence.begin(), element_size - 1), element_size);		// Push b1 into main
	_push_elem(main, _next(sequence.begin(), 2 * element_size - 1), element_size);	// Push a1 into main

	Iterator start = _next(sequence.begin(), 2 * element_size); // Starting from b2
	Iterator last = _next(sequence.begin(), (element_size * nbr_of_elems));
	Iterator end = _next(last, -(is_odd * element_size));
	
	for (Iterator it = start; it != end; std::advance(it, 2 * element_size)) {

		Iterator	b_elem = _next(it, element_size - 1);
		Iterator	a_elem = _next(it, 2 * element_size - 1);

		_push_elem(pend, b_elem, element_size);
		_push_elem(main, a_elem, element_size);
	}

	if (is_odd)
	{
		_push_elem(pend, _next(end, element_size - 1), element_size);
	}

	while (last != sequence.end())
	{
		non.insert(non.end(), *last);
		last++;
	}

	/* DEBUG */
	std::cout << "main: ";
	for (Iterator it = main.begin(); it != main.end(); std::advance(it, 1))
		std::cout << *it;
	std::cout << std::endl;
	std::cout << "pend: ";
	for (Iterator it = pend.begin(); it != pend.end(); std::advance(it, 1))
		std::cout << *it;
	std::cout << std::endl;
	std::cout << "non: ";
	for (Iterator it = non.begin(); it != non.end(); std::advance(it, 1))
		std::cout << *it;
	std::cout << std::endl;
	return;

	/* DEBUG END */

	_insert_pend_into_main(main, pend, comps_counter);

	sequence.clear();
	for (Iterator it = main.begin(); it != main.end(); std::advance(it, 1))
		sequence.insert(sequence.end(), *it);
	for (Iterator it = non.begin(); it != non.end(); std::advance(it, 1))
		sequence.insert(sequence.end(), *it);

	if (element_size > 1)
		_initalize_main_and_pend(sequence, element_size / 2, comps_counter);

}	

template <typename T> void PmergeMe::_insert_pend_into_main(T &main, T &pend, int & comps_counter) {
	(void) main;
	(void) pend;
	(void) comps_counter;
}
