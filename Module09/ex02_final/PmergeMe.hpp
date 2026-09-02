#pragma once
#include <iterator>
#include <vector>
#include <deque>

class PmergeMe {

	private:
		template <typename T>
		static void			 _initalize_main_and_pend(T &sequence, unsigned int pair_size);
		template <typename T>
		static void			_insert_pend_into_main(T &main, T &pend);

		template <typename T>
		static unsigned int	_split_into_pairs_and_sort(T &sequence, int &comps_counter, unsigned int element_size = 1);

		template <typename It>
		static bool			_comp(It lv, It rv, int &comps_counter);

		template <typename It>
		static It			_next(It it, int steps);

		template <typename It>
		static void			_swap_elems(It first_elem, unsigned int element_size);

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

template <typename It> void	PmergeMe::_swap_elems(It first_elem, unsigned int element_size) {

	It start = _next(first_elem, -element_size + 1);
	It end = _next(first_elem, 1);

	while (start != end)
	{
		std::iter_swap(start, _next(start, element_size));
		start++;
	}
}


template <typename T> T	PmergeMe::ford_johnson_merge_insertion_sort(T sequence, int &comps_counter) {

	unsigned int	element_size;

	element_size = _split_into_pairs_and_sort(sequence, comps_counter);
	(void) element_size;
	//_initalize_main_and_pend(sequence, element_size);

	return sequence;
}

template <typename T> unsigned int PmergeMe::_split_into_pairs_and_sort(T &sequence, int &comps_counter, unsigned int element_size) {

	typedef typename T::iterator Iterator;

	unsigned int	nbr_of_elems;

	nbr_of_elems = sequence.size() / element_size;
	if (nbr_of_elems < 2)
		return element_size;

	bool is_odd = nbr_of_elems % 2;

	Iterator start = sequence.begin();
	Iterator last = _next(sequence.begin(), (element_size * nbr_of_elems));
	Iterator end = _next(last, -(is_odd * element_size));

	unsigned int pair_size = element_size * 2;
	for (Iterator it = start ; it != end; std::advance(it, pair_size)) {

		Iterator this_elem = _next(it, element_size - 1);
		Iterator next_elem = _next(it, pair_size - 1);
		if (_comp(next_elem, this_elem, comps_counter))
			_swap_elems(this_elem, element_size);
	}
	return _split_into_pairs_and_sort(sequence, comps_counter, element_size * 2);
}
