#include <iostream>
#include <string>
#include "Array.hpp"

#define YELLOW "\033[0;33m"
#define GREEN  "\033[0;32m"
#define RED    "\033[0;31m"
#define RESET  "\033[0m"

int main(void)
{
	std::cout << YELLOW << "-- default ctor (empty) --" << RESET << std::endl;
	Array<int> empty;
	std::cout << "size = " << empty.size() << std::endl;

	std::cout << YELLOW << "-- ctor with n, default-initialized --" << RESET << std::endl;
	Array<int> a(5);
	for (size_t i = 0; i < a.size(); ++i)
		a[i] = static_cast<int>(i * 10);
	for (size_t i = 0; i < a.size(); ++i)
		std::cout << "a[" << i << "] = " << a[i] << std::endl;

	std::cout << YELLOW << "-- copy ctor: independence check --" << RESET << std::endl;
	Array<int> b(a);
	b[0] = 999;
	std::cout << "a[0] = " << a[0] << " (unchanged), b[0] = " << b[0] << std::endl;

	std::cout << YELLOW << "-- copy assignment: independence check --" << RESET << std::endl;
	Array<int> c;
	c = a;
	c[1] = 111;
	std::cout << "a[1] = " << a[1] << " (unchanged), c[1] = " << c[1] << std::endl;

	std::cout << YELLOW << "-- string Array --" << RESET << std::endl;
	Array<std::string> s(3);
	s[0] = "chaine1";
	s[1] = "chaine2";
	s[2] = "chaine3";
	for (size_t i = 0; i < s.size(); ++i)
		std::cout << s[i] << " ";
	std::cout << std::endl;

	std::cout << YELLOW << "-- out of bounds access --" << RESET << std::endl;
	try
	{
		std::cout << a[a.size()] << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << RED << "caught: " << e.what() << RESET << std::endl;
	}

	std::cout << GREEN << "OK" << RESET << std::endl;

	return (0);
}
