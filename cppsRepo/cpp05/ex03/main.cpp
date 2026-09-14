#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	Bureaucrat boss("Boss", 1);
	Intern someRandomIntern;

	AForm* forms[4];
	forms[0] = someRandomIntern.makeForm("shrubbery creation", "home");
	forms[1] = someRandomIntern.makeForm("robotomy request", "Bender");
	forms[2] = someRandomIntern.makeForm("presidential pardon", "Zaphod");
	forms[3] = someRandomIntern.makeForm("form 28C", "nowhere");

	for (int i = 0; i < 4; i++) {
		if (forms[i]) {
			boss.signForm(*forms[i]);
			boss.executeForm(*forms[i]);
			delete forms[i];
		}
	}
}
