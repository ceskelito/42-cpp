#pragma once

// Costruttore di default: crea array di 1 elemento inizializzato a 0
template<typename T>
Array<T>::Array(void): _size(1), _elem(new T[_size]()) {}

// Costruttore con parametro: crea array di n elementi inizializzati a 0
template<typename T>
Array<T>::Array(unsigned int n): _size(n), _elem(new T[_size]()) {}

// Copy constructor: copia profonda dell'array
template<typename T>
Array<T>::Array(Array const & other): _size(other._size), _elem(new T[_size]()) {
	for (size_t i = 0; i < _size; i++) {
		_elem[i] = other._elem[i];
	}
}

// Distruttore: dealloca la memoria dell'array
template<typename T>
Array<T>::~Array(void) {
	delete[] _elem;
}

// Operatore di assegnamento: copia profonda con autoassignamento sicuro
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

// Operatore [] per accedere agli elementi con controllo dei limiti
template<typename T>
T&	Array<T>::operator[](unsigned int const & n) const {
	if (n >= _size)
		throw std::out_of_range("Out of range access");
	return _elem[n];
}

// Ritorna la dimensione dell'array
template<typename T>
size_t	Array<T>::size(void) const {
	return _size;
}
