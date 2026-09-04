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

	//std::cout << "----- ShrubberyCreationForm -----" << std::endl;
	//ShrubberyCreationForm shrub("home");
	//lowGrade.signForm(shrub);
	//highGrade.signForm(shrub);
	//lowGrade.executeForm(shrub);
	//highGrade.executeForm(shrub);

	std::cout << "----- RobotomyRequestForm -----" << std::endl;
	RobotomyRequestForm robo("Bender");
	highGrade.signForm(robo);
	highGrade.executeForm(robo);

	std::cout << "----- RobotomyRequestForm 2 -----" << std::endl;
	RobotomyRequestForm robo2("Bender2");
	highGrade.signForm(robo2);
	highGrade.executeForm(robo2);

	std::cout << "----- RobotomyRequestForm 3 -----" << std::endl;
	RobotomyRequestForm robo3("Bender3");
	highGrade.signForm(robo3);
	highGrade.executeForm(robo3);

	std::cout << "----- RobotomyRequestForm 4 -----" << std::endl;
	RobotomyRequestForm robo4("Bender4");
	highGrade.signForm(robo4);
	highGrade.executeForm(robo4);

	//std::cout << "----- PresidentialPardonForm -----" << std::endl;
	//PresidentialPardonForm pardon("Zaphod");
	//highGrade.signForm(pardon);
	//highGrade.executeForm(pardon);

	//std::cout << "----- Unsigned form execute attempt -----" << std::endl;
	//PresidentialPardonForm unsignedPardon("Nobody");
	//highGrade.executeForm(unsignedPardon);

	std::cout << "----- Gecersiz grade ile Bureaucrat olusturma -----" << std::endl;
	try {
		Bureaucrat invalid("Invalid", 151);
		(void)invalid;
	} catch (std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
}
