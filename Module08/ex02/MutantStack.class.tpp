#include "MutantStack.class.hpp"

template <typename T, typename Container>
MutantStack<T, Container>::
	MutantStack( void ):
		std::stack<T, Container>() {}

template <typename T, typename Container>
MutantStack<T, Container>::
	MutantStack( MutantStack const & other ):
		std::stack<T, Container>(other) {}

template <typename T, typename Container>
MutantStack<T, Container>::
	~MutantStack( void ) {}

template <typename T, typename Container>
MutantStack<T, Container> & 
	MutantStack<T, Container>::
		operator=(MutantStack const & other)
{
			std::stack<T, Container>::operator=(other);
			return *this;
}

template <typename T, typename Container>
typename MutantStack<T, Container>::iterator
	MutantStack<T, Container>::begin()
{
	return this->c.begin();
}

template <typename T, typename Container>
typename MutantStack<T, Container>::const_iterator
	MutantStack<T, Container>::begin() const
{
	return this->c.begin();
}

template <typename T, typename Container>
typename MutantStack<T, Container>::iterator
	MutantStack<T, Container>::rbegin()
{
	return this->c.rbegin();
}

template <typename T, typename Container>
typename MutantStack<T, Container>::const_iterator
	MutantStack<T, Container>::rbegin() const
{
	return this->c.rbegin();
}

template <typename T, typename Container>
typename MutantStack<T, Container>::iterator
	MutantStack<T, Container>::end()
{
	return this->c.end();
}

template <typename T, typename Container>
typename MutantStack<T, Container>::const_iterator
	MutantStack<T, Container>::end() const
{
	return this->c.end();
}

template <typename T, typename Container>
typename MutantStack<T, Container>::iterator
	MutantStack<T, Container>::rend()
{
	return this->c.rend();
}

template <typename T, typename Container>
typename MutantStack<T, Container>::const_iterator
	MutantStack<T, Container>::rend() const
{
	return this->c.rend();
}
