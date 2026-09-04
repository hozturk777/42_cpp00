#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept>

class Span
{
	public:
		Span(unsigned int n);
		Span(const Span &src);
		Span &operator=(const Span &src);
		~Span();

		void addNumber(int n);

		template <typename InputIterator>
		void addRange(InputIterator first, InputIterator last)
		{
			if (_maxSize - _numbers.size() < static_cast<unsigned int>(std::distance(first, last)))
				throw std::length_error("Span: not enough space left");
			_numbers.insert(_numbers.end(), first, last);
		}

		int shortestSpan() const;
		int longestSpan() const;

	private:
		Span();

		unsigned int      _maxSize;
		std::vector<int>  _numbers;
};

#endif
