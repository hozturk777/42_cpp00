#include "Span.hpp"
#include <algorithm>

Span::Span() : _maxSize(0)
{
}

Span::Span(unsigned int n) : _maxSize(n)
{
	_numbers.reserve(n);
}

Span::Span(const Span &src) : _maxSize(src._maxSize), _numbers(src._numbers)
{
}

Span &Span::operator=(const Span &src)
{
	if (this != &src)
	{
		_maxSize = src._maxSize;
		_numbers = src._numbers;
	}
	return *this;
}

Span::~Span()
{
}

void Span::addNumber(int n)
{
	if (_numbers.size() >= _maxSize)
		throw std::length_error("Span: full");
	_numbers.push_back(n);
}

int Span::shortestSpan() const
{
	if (_numbers.size() < 2)
		throw std::length_error("Span: not enough numbers");

	std::vector<int> sorted(_numbers);
	std::sort(sorted.begin(), sorted.end());

	int shortest = sorted[1] - sorted[0];
	for (std::vector<int>::size_type i = 2; i < sorted.size(); ++i)
	{
		int diff = sorted[i] - sorted[i - 1];
		if (diff < shortest)
			shortest = diff;
	}
	return shortest;
}

int Span::longestSpan() const
{
	if (_numbers.size() < 2)
		throw std::length_error("Span: not enough numbers");

	std::vector<int>::const_iterator minIt = std::min_element(_numbers.begin(), _numbers.end());
	std::vector<int>::const_iterator maxIt = std::max_element(_numbers.begin(), _numbers.end());
	return *maxIt - *minIt;
}
