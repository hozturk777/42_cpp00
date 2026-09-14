#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : _name("Default"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150) {
	std::cout << GOLD"[Form] Default Constructor called" RESET << std::endl;
}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw Form::GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw Form::GradeTooLowException();
	std::cout << GOLD"[Form] Parameterized Constructor called" RESET << std::endl;
}

Form::Form(const Form& copy)
	: _name(copy._name), _isSigned(copy._isSigned), _gradeToSign(copy._gradeToSign), _gradeToExecute(copy._gradeToExecute) {
	std::cout << GOLD"[Form] Copy Constructor called" RESET << std::endl;
}

Form& Form::operator=(const Form& copy) {
	std::cout << GOLD"[Form] Copy assignment operator called" RESET << std::endl;
	if (this != &copy)
		this->_isSigned = copy._isSigned;
	return (*this);
}

Form::~Form() {
	std::cout << RED"[Form] Destruct called" RESET << std::endl;
}

std::string	Form::getName() const {
	return (this->_name);
}

bool	Form::getIsSigned() const {
	return (this->_isSigned);
}

int	Form::getGradeToSign() const {
	return (this->_gradeToSign);
}

int	Form::getGradeToExecute() const {
	return (this->_gradeToExecute);
}

void	Form::beSigned(const Bureaucrat& bureaucrat) {
	if (bureaucrat.getGrade() > this->_gradeToSign)
		throw Form::GradeTooLowException();
	this->_isSigned = true;
}

const char*	Form::GradeTooHighException::what() const throw() {
	return ("Grade is too high");
}

const char*	Form::GradeTooLowException::what() const throw() {
	return ("Grade is too low");
}

std::ostream&	operator<<(std::ostream& os, const Form& form) {
	os << form.getName() << ", form grade to sign: " << form.getGradeToSign()
		<< ", grade to execute: " << form.getGradeToExecute()
		<< ", signed: " << (form.getIsSigned() ? "yes" : "no");
	return (os);
}
