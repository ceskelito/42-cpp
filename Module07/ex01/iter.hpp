#pragma once
template<typename T, typename Func>
void	iter(T *array, int const len, Func f) {
	for (int i = 0; i < len; i++)
		f(array[i]);
}
