#pragma once
#include <iterator>

class PmergeMe {

	private:
		template <typename It>
		static bool			_comp(It lv, It rv, int &comps_counter);

		template <typename It>
		static It			_next(It it, int steps);

		template <typename It>
		static void			_swap_elems(It first_elem, int element_size);

		template <typename T>
		static typename T::iterator	_element_begin(T &container, int element_index, int element_size);

		template <typename T>
		static typename T::iterator	_element_last(T &container, int element_index, int element_size);

		template <typename T>
		static typename T::iterator	_element_end(T &container, int element_index, int element_size);

		template <typename T>
		static int			_upper_bound_element_index(T &main, int bound_idx, T &pend, int source_idx, int element_size, int &comps_counter);

		template <typename T>
		static void			_append_element(T &dst, T &src, int source_idx, int element_size);

		template <typename T>
		static void			_insert_element_before(T &dst, int target_idx, T &src, int source_idx, int element_size);

		template <typename T>
		static void			_erase_element(T &container, int element_index, int element_size);

		template <typename T>
		static void			_ford_johnson_merge_insertion_sort(T &sequence, int element_size, int &comps_counter);

	public:
		template <typename T>
		static T			sort(T sequence, int &comps_counter);
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
int PmergeMe::_upper_bound_element_index(T &main, int bound_idx, T &pend, int source_idx, int element_size, int &comps_counter)
{
	int lo = 0;
	int hi = bound_idx;
	while (lo < hi)
	{
		int mid = lo + (hi - lo) / 2;
		if (_comp(_element_last(pend, source_idx, element_size),
				  _element_last(main, mid, element_size), comps_counter))
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
void PmergeMe::_insert_element_before(T &dst, int target_idx, T &src, int source_idx, int element_size)
{
	dst.insert(_element_begin(dst, target_idx, element_size),
			   _element_begin(src, source_idx, element_size),
			   _element_end(src, source_idx, element_size));
}

template <typename T>
void PmergeMe::_erase_element(T &container, int element_index, int element_size)
{
	container.erase(_element_begin(container, element_index, element_size),
				_element_end(container, element_index, element_size));
}


#include <cmath>
// int	getJacobsthalNumber(int index);
// int	getJacobsthalNumber(int index) {
// 	return ( (std::pow(2, index+1) + std::pow(-1, index)) / 3 );
// }
#define JACO(index) ((std::pow(2, index+1) + std::pow(-1, index)) / 3 )

template <typename T> void PmergeMe::_ford_johnson_merge_insertion_sort(T &sequence, int element_size, int &comps_counter) {

	typedef typename T::iterator Iterator;

	int	nbr_of_elems = sequence.size() / element_size;

	if (nbr_of_elems < 2)
		return ;

	bool is_odd = nbr_of_elems % 2;

	Iterator start = sequence.begin();
	Iterator last = _next(sequence.begin(), (element_size * nbr_of_elems));
	Iterator end = _next(last, -(is_odd * element_size));

	int pair_size = element_size * 2;
	for (Iterator it = start ; it != end; std::advance(it, pair_size))
	{
		Iterator this_elem = _next(it, element_size - 1);
		Iterator next_elem = _next(it, pair_size - 1);

		if (_comp(next_elem, this_elem, comps_counter))
			_swap_elems(this_elem, element_size);
	}

	_ford_johnson_merge_insertion_sort(sequence, element_size * 2, comps_counter);

	int full_values = nbr_of_elems * element_size;
	int non_values = static_cast<int>(sequence.size()) - full_values;

	T main, pend, non;

	main.insert(main.end(), sequence.begin(), _next(sequence.begin(), element_size * 2));
	for (int element_index = 2; element_index < nbr_of_elems; element_index += 2)
	{
		_append_element(pend, sequence, element_index, element_size);
		if (element_index + 1 < nbr_of_elems)
			_append_element(main, sequence, element_index + 1, element_size);
	}
	if (non_values > 0)
	{
		non.insert(non.end(), _next(sequence.begin(), full_values), sequence.end());
	}

	int nbr_main_elements = static_cast<int>(main.size() / element_size);
	int nbr_pend_elements = static_cast<int>(pend.size() / element_size);

	int	prev_jacobsthal = JACO(1);
	int	inserted_numbers = 0;
	for (int k = 2 ;; k++)
	{
		int curr_jacobsthal = JACO(k);
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
			int insert_pos = _upper_bound_element_index(main, search_end, pend, source_element, element_size, comps_counter);
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
		int insert_pos = _upper_bound_element_index(main, search_end, pend, source_element, element_size, comps_counter);
		_insert_element_before(main, insert_pos, pend, source_element, element_size);
		_erase_element(pend, source_element, element_size);
		nbr_main_elements++;
		nbr_pend_elements--;

    }

	sequence.clear();
	sequence.insert(sequence.end(), main.begin(), main.end());
	sequence.insert(sequence.end(), non.begin(), non.end());

}

template <typename T> T PmergeMe::sort(T sequence, int &comps_counter) {
	_ford_johnson_merge_insertion_sort(sequence, 1, comps_counter);
	return sequence;
}
