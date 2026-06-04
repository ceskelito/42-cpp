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

template<typename T>
Array<T>::Array(void): _size(1), _elem(new T[_size]()) {};

template<typename T>
Array<T>::Array(unsigned int n): _size(n), _elem(new T[_size]()) {};

template<typename T>
Array<T>::Array(Array const & other): _size(other._size) {
	_elem = new T[_size]();
	for (size_t i = 0; i < _size; i++) {
		_elem[i] = other._elem[i];
	}
}

template<typename T>
Array<T>::~Array(void) {
	delete[] _elem;
}

template<typename T>
Array<T> Array<T>::operator=(Array const & other) {
	if (this != &other) 
	{
		delete[] _elem;
		_size = other._size;
		_elem = new T[_size]();
		for (size_t i = 0; i < _size; i++) {
			_elem[i] = other._elem[i];
		}
	}
	return *this;
}

template<typename T>
T&	Array<T>::operator[](unsigned int const & n) const {
	if (n >= _size)
		throw std::out_of_range("Out of range access");
	return _elem[n];
}

template<typename T>
size_t	Array<T>::size(void) const {
	return _size;
}
