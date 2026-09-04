#pragma once

class PmergeMe {

	private:
		template <typename It>
		static bool		_comp(It lv, It rv, int &nbr_of_comparisons);

		template <typename It>
		static It
						_next(It it, int steps);

		template <typename It>
		static void		_swap_elems(It first_elem, int element_size);

		template <typename T>
		static typename T::iterator
						_element_begin(T &container, int element_index, int element_size);

		template <typename T>
		static typename T::iterator
						_element_last(T &container, int element_index, int element_size);

		template <typename T>
		static typename T::iterator
						_element_end(T &container, int element_index, int element_size);

		template <typename T>
		static int		_upper_bound_element_index(T &main, int bound_idx, T &pend, int source_idx, int element_size, int &nbr_of_comparisons);

		template <typename T>
		static void		_append_element(T &dst, T &src, int source_idx, int element_size);

		template <typename T>
		static void		_insert_element_before(T &dst, int target_idx, T &src, int source_idx, int element_size);

		template <typename T>
		static void		_erase_element(T &container, int element_index, int element_size);

		template <typename T>
		static void		_ford_johnson_merge_insertion_sort(T &sequence, int element_size, int &nbr_of_comparisons);

		static int 		_jacobsthal_number(int index);
	public:
		template <typename T>
		static int		sort(T &sequence);
};

#include "PmergeMe.tpp"