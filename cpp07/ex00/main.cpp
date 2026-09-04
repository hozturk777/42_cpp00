#include <iostream>
#include <string>
#include "whatever.hpp"

#define GREEN  "\033[0;32m"
#define YELLOW "\033[0;33m"
#define CYAN   "\033[0;36m"
#define RESET  "\033[0m"

int main(void)
{
	std::cout << YELLOW << "-- int --" << RESET << std::endl;

	int a = 2;
	int b = 3;

	::swap(a, b);
	std::cout << "a = " << CYAN << a << RESET << ", b = " << CYAN << b << RESET << std::endl;
	std::cout << "min(a, b) = " << GREEN << ::min(a, b) << RESET << std::endl;
	std::cout << "max(a, b) = " << GREEN << ::max(a, b) << RESET << std::endl;

	std::cout << YELLOW << "-- string --" << RESET << std::endl;

	std::string c = "chaine1";
	std::string d = "chaine2";

	::swap(c, d);
	std::cout << "c = " << CYAN << c << RESET << ", d = " << CYAN << d << RESET << std::endl;
	std::cout << "min(c, d) = " << GREEN << ::min(c, d) << RESET << std::endl;
	std::cout << "max(c, d) = " << GREEN << ::max(c, d) << RESET << std::endl;

	return (0);
}
