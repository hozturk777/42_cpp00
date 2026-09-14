#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"
#include <iostream>

PresidentialPardonForm::PresidentialPardonForm()
	: AForm("Presidential Pardon Form", 25, 5), _target("default") {
		std::cout << GOLD"[PresidentialPardonForm] Default Constructor called" RESET << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
	: AForm("Presidential Pardon Form", 25, 5), _target(target) {
		std::cout << GOLD"[PresidentialPardonForm] Parameterized Constructor called" RESET << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& copy)
	: AForm(copy), _target(copy._target) {
		std::cout << GOLD"[PresidentialPardonForm] Copy Constructor called" RESET << std::endl;
}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& copy) {
	std::cout << GOLD"[PresidentialPardonForm] Copy assignment operator called" RESET << std::endl;
	if (this != &copy) {
		AForm::operator=(copy);
		this->_target = copy._target;
	}
	return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm() {
	std::cout << RED"[PresidentialPardonForm] Destruct called" RESET << std::endl;
}

void	PresidentialPardonForm::executeAction() const {
	std::cout << this->_target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}
