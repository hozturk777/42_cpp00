#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

Intern::Intern() {
	std::cout << GOLD"[Intern] Default Constructor called" RESET << std::endl;
}

Intern::Intern(const Intern& copy) {
	(void)copy;
	std::cout << GOLD"[Intern] Copy Constructor called" RESET << std::endl;
}

Intern& Intern::operator=(const Intern& copy) {
	std::cout << GOLD"[Intern] Copy assignment operator called" RESET << std::endl;
	(void)copy;
	return (*this);
}

Intern::~Intern() {
	std::cout << RED"[Intern] Destruct called" RESET << std::endl;
}

AForm*	Intern::createShrubbery(const std::string& target) {
	return (new ShrubberyCreationForm(target));
}

AForm*	Intern::createRobotomy(const std::string& target) {
	return (new RobotomyRequestForm(target));
}

AForm*	Intern::createPardon(const std::string& target) {
	return (new PresidentialPardonForm(target));
}

AForm*	Intern::makeForm(const std::string& formName, const std::string& target) const {
	struct FormEntry {
		const char*		name;
		AForm*			(*create)(const std::string&);
	};

	const FormEntry	forms[] = {
		{"shrubbery creation", &Intern::createShrubbery},
		{"robotomy request", &Intern::createRobotomy},
		{"presidential pardon", &Intern::createPardon}
	};
	const size_t		formsCount = sizeof(forms) / sizeof(forms[0]);

	for (size_t i = 0; i < formsCount; i++) {
		if (formName == forms[i].name) {
			AForm* form = forms[i].create(target);
			std::cout << "Intern creates " << *form << std::endl;
			return (form);
		}
	}
	std::cout << "Intern couldn't find a form named \"" << formName << "\"" << std::endl;
	return (NULL);
}
