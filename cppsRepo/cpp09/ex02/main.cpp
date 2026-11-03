#include "PmergeMe.hpp"
#include <ctime>
#include <exception>
#include <iomanip>
#include <iostream>

static double elapsedUs(std::clock_t start)
{
	return static_cast<double>(std::clock() - start) * 1000000.0 / CLOCKS_PER_SEC;
}

int main(int argc, char** argv)
{
	PmergeMe pm;
	double vecTime;
	double deqTime;

	try
	{
		std::clock_t start = std::clock();
		pm.loadVector(argc, argv);
		pm.sortVector();
		vecTime = elapsedUs(start);

		start = std::clock();
		pm.loadDeque(argc, argv);
		pm.sortDeque();
		deqTime = elapsedUs(start);
	}
	catch (const std::exception&)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	std::cout << "Before:";
	for (int i = 1; i < argc; ++i)
		std::cout << " " << argv[i];
	std::cout << std::endl;

	std::cout << "After:";
	for (size_t i = 0; i < pm.getVector().size(); ++i)
		std::cout << " " << pm.getVector()[i];
	std::cout << std::endl;

	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << pm.getVector().size()
			  << " elements with std::vector : " << vecTime << " us" << std::endl;
	std::cout << "Time to process a range of " << pm.getDeque().size()
			  << " elements with std::deque : " << deqTime << " us" << std::endl;
	return 0;
}
