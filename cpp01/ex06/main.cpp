#include <iostream>
#include "Harl.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Invalid Argument" << std::endl;
		return 1;
	}
	Harl test;

	test.complain(av[1]);
	return 0;
}