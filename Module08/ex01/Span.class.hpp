#include <vector>

class Span {

	private:
		
		unsigned			_size;
		std::vector<int>	_v;

	public:

		Span();
		Span(unsigned const n);
		Span(Span const & other);
		Span& operator=(Span const & other);

		void		addNumber(unsigned const & n);
		unsigned	shortestSpan() const;
		unsigned	longestSpan() const;

};
