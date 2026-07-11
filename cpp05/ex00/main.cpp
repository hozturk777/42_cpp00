#include "Bureaucrat.hpp"
#include <iostream>

int main()
{
	Bureaucrat huso("Huso", 112);
	Bureaucrat memo = huso;
	Bureaucrat femo(memo);
	memo.decGrade();
	femo.incGrade();
	std::cout << huso << std::endl;
	std::cout << memo << std::endl;
	std::cout << femo << std::endl;
}