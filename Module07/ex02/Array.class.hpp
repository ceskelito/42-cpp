#pragma once
#include <stdexcept>

template <typename T>
class Array {

	private:
		size_t	_size;
		T*		_elem;

	public:
		Array(void);
		Array(unsigned int n);
		Array(Array const & other);
		~Array(void);

		Array	operator=(Array const & other);
		T&		operator[](unsigned int const &n) const;

		size_t	size(void) const;
};

#include "Array.class.tpp"
