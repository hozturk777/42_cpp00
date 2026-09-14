#include "Bureaucrat.hpp"
#include <iostream>

int main()
{
	std::cout << "----- Normal kullanim -----" << std::endl;
	Bureaucrat huso("Huso", 50);
	Bureaucrat memo = huso;
	Bureaucrat femo(memo);
	memo.incGrade();
	femo.decGrade();
	std::cout << huso << std::endl;
	std::cout << memo << std::endl;
	std::cout << femo << std::endl;

	std::cout << "----- Gecersiz grade ile constructor (too high) -----" << std::endl;
	try {
		Bureaucrat invalid("Invalid", 151);
		(void)invalid;
	} catch (std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}

	std::cout << "----- Gecersiz grade ile constructor (too low) -----" << std::endl;
	try {
		Bureaucrat invalid("Invalid", 0);
		(void)invalid;
	} catch (std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}

	std::cout << "----- Sinirda incGrade (grade 1 -> too high) -----" << std::endl;
	try {
		Bureaucrat top("Top", 1);
		top.incGrade();
	} catch (std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}

	std::cout << "----- Sinirda decGrade (grade 150 -> too low) -----" << std::endl;
	try {
		Bureaucrat bottom("Bottom", 150);
		bottom.decGrade();
	} catch (std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
}
