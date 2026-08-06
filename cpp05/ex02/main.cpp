#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	Bureaucrat lowGrade("Newbie", 150);
	Bureaucrat highGrade("Boss", 1);

	std::cout << "----- ShrubberyCreationForm -----" << std::endl;
	ShrubberyCreationForm shrub("home");
	lowGrade.signForm(shrub);
	highGrade.signForm(shrub);
	lowGrade.executeForm(shrub);
	highGrade.executeForm(shrub);

	std::cout << "----- RobotomyRequestForm -----" << std::endl;
	RobotomyRequestForm robo("Bender");
	highGrade.signForm(robo);
	highGrade.executeForm(robo);

	std::cout << "----- PresidentialPardonForm -----" << std::endl;
	PresidentialPardonForm pardon("Zaphod");
	highGrade.signForm(pardon);
	highGrade.executeForm(pardon);

	std::cout << "----- Unsigned form execute attempt -----" << std::endl;
	PresidentialPardonForm unsignedPardon("Nobody");
	highGrade.executeForm(unsignedPardon);

	try {
		ShrubberyCreationForm badForm;
		(void)badForm;
	} catch (std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
}
