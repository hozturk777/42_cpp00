#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

RobotomyRequestForm::RobotomyRequestForm()
	: AForm("Robotomy Request Form", 72, 45), _target("default") {
		std::cout << GOLD"[RobotomyRequestForm] Default Constructor called" RESET << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
	: AForm("Robotomy Request Form", 72, 45), _target(target) {
		std::cout << GOLD"[RobotomyRequestForm] Parameterized Constructor called" RESET << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& copy)
	: AForm(copy), _target(copy._target) {
		std::cout << GOLD"[RobotomyRequestForm] Copy Constructor called" RESET << std::endl;
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& copy) {
	std::cout << GOLD"[RobotomyRequestForm] Copy assignment operator called" RESET << std::endl;
	if (this != &copy) {
		AForm::operator=(copy);
		this->_target = copy._target;
	}
	return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm() {
	std::cout << RED"[RobotomyRequestForm] Destruct called" RESET << std::endl;
}

void	RobotomyRequestForm::executeAction() const {
	std::cout << "* drilling noises *" << std::endl;
	if (std::rand() % 2)
		std::cout << this->_target << " has been robotomized successfully" << std::endl;
	else
		std::cout << "robotomy of " << this->_target << " failed" << std::endl;
}
