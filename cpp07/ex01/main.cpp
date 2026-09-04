#include <iostream>
#include <string>
#include "iter.hpp"

#define YELLOW "\033[0;33m"
#define GREEN  "\033[0;32m"
#define RESET  "\033[0m"

template <typename T>
void printElem(T const &elem)
{
	std::cout << elem << " ";
}

template <typename T>
void doubleElem(T &elem)
{
	elem *= 2;
}

int main(void)
{
	std::cout << YELLOW << "-- int array --" << RESET << std::endl;

	int arr[] = {1, 2, 3, 4, 5};
	size_t len = sizeof(arr) / sizeof(arr[0]);

	iter(arr, len, printElem<int>);
	std::cout << std::endl;

	iter(arr, len, doubleElem<int>);
	iter(arr, len, printElem<int>);
	std::cout << std::endl;

	std::cout << YELLOW << "-- const int array (const-ref function only) --" << RESET << std::endl;

	int const carr[] = {10, 20, 30};
	iter(carr, static_cast<size_t>(3), printElem<int>);
	std::cout << std::endl;

	std::cout << YELLOW << "-- string array --" << RESET << std::endl;

	std::string sarr[] = {"chaine1", "chaine2", "chaine3"};
	iter(sarr, static_cast<size_t>(3), printElem<std::string>);
	std::cout << std::endl;

	std::cout << GREEN << "OK" << RESET << std::endl;

	return (0);
}
