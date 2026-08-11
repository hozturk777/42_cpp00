#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("Shrubbery Creation Form", 145, 137), _target("default") {
		std::cout << GOLD"[ShrubberyCreationForm] Default Constructor called" RESET << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
	: AForm("Shrubbery Creation Form", 145, 137), _target(target) {
		std::cout << GOLD"[ShrubberyCreationForm] Parameterized Constructor called" RESET << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& copy)
	: AForm(copy), _target(copy._target) {
		std::cout << GOLD"[ShrubberyCreationForm] Copy Constructor called" RESET << std::endl;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& copy) {
	std::cout << GOLD"[ShrubberyCreationForm] Copy assignment operator called" RESET << std::endl;
	if (this != &copy) {
		AForm::operator=(copy);
		this->_target = copy._target;
	}
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
	std::cout << RED"[ShrubberyCreationForm] Destruct called" RESET << std::endl;
}

void	ShrubberyCreationForm::executeAction() const {
	std::ofstream	file((this->_target + "_shrubbery").c_str());

	file << "       *\n"
			"      ***\n"
			"     *****\n"
			"    *******\n"
			"       |\n";
	file.close();
}
