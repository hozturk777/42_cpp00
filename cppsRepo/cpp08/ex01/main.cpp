#include <iostream>
#include <vector>
#include <cstdlib>
#include "Span.hpp"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

int main(void)
{
	Span sp = Span(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	try
	{
		sp.addNumber(1);
	}
	catch (const std::exception &e)
	{
		std::cout << RED << "addNumber overflow: " << e.what() << RESET << std::endl;
	}

	Span empty(5);
	try
	{
		empty.shortestSpan();
	}
	catch (const std::exception &e)
	{
		std::cout << RED << "shortestSpan empty: " << e.what() << RESET << std::endl;
	}

	std::vector<int> src;
	for (int i = 0; i < 100; ++i)
		src.push_back(i);

	Span ranged(100);
	ranged.addRange(src.begin(), src.end());
	std::cout << GREEN << "ranged shortest: " << ranged.shortestSpan() << RESET << std::endl;
	std::cout << GREEN << "ranged longest: " << ranged.longestSpan() << RESET << std::endl;

	Span big(10000);
	for (int i = 0; i < 10000; ++i)
		big.addNumber(std::rand());
	std::cout << GREEN << "big shortest: " << big.shortestSpan() << RESET << std::endl;
	std::cout << GREEN << "big longest: " << big.longestSpan() << RESET << std::endl;

	Span copy(big);
	std::cout << GREEN << "copy longest: " << copy.longestSpan() << RESET << std::endl;

	return 0;
}
