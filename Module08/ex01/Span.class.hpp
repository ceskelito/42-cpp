#include <vector>

class Span {

	typedef std::vector<int>::const_iterator vec_iter;

	private:
		unsigned			_size;
		std::vector<int>	_v;

	public:

		Span(void);
		Span(unsigned const n);
		Span(Span const & other);
		~Span(void);
		Span& operator=(Span const & other);

		void		addNumber(unsigned const & n);
		void		addRange(vec_iter & begin, vec_iter & end);
		void		addRange(unsigned const & count, int const & value);
		unsigned	shortestSpan() const;
		unsigned	longestSpan() const;

};
