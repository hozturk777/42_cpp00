#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

int main(void)
{
	std::vector<int> vec;
	vec.push_back(2);
	vec.push_back(4);
	vec.push_back(6);
	vec.push_back(8);

	std::list<int> lst;
	lst.push_back(10);
	lst.push_back(20);
	lst.push_back(30);

	try
	{
		std::vector<int>::iterator it = easyfind(vec, 6);
		std::cout << GREEN << "vec: found " << *it << RESET << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << RED << "vec: " << e.what() << RESET << std::endl;
	}

	try
	{
		std::vector<int>::iterator it = easyfind(vec, 42);
		std::cout << GREEN << "vec: found " << *it << RESET << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << RED << "vec: " << e.what() << RESET << std::endl;
	}

	try
	{
		std::list<int>::iterator it = easyfind(lst, 20);
		std::cout << GREEN << "lst: found " << *it << RESET << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << RED << "lst: " << e.what() << RESET << std::endl;
	}

	return 0;
}
