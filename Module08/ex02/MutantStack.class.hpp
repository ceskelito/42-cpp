#pragma once

#include <stack>
#include <deque>

template <typename T, typename Container = std::deque<T> >
class MutantStack: public std::stack<T, Container> {

	public:
		typedef	typename Container::iterator		iterator;
		typedef typename Container::const_iterator	const_iterator;
		// using	typename Container::iterator;
		// using	typename Container::const_iterator;

		iterator	begin() const;
		iterator	end()	const;
		iterator	rbegin() const;
		iterator	rend() const;


		MutantStack( void );
		MutantStack( MutantStack const & other );
		~MutantStack( void );
		MutantStack& operator=( MutantStack const & other );
};

#include "MutantStack.class.tpp"
