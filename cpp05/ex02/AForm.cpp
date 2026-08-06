#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : _name("Default"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150) {
	std::cout << GOLD"[AForm] Default Constructor called" RESET << std::endl;
}

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw AForm::GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw AForm::GradeTooLowException();
	std::cout << GOLD"[AForm] Parameterized Constructor called" RESET << std::endl;
}

AForm::AForm(const AForm& copy)
	: _name(copy._name), _isSigned(copy._isSigned), _gradeToSign(copy._gradeToSign), _gradeToExecute(copy._gradeToExecute) {
	std::cout << GOLD"[AForm] Copy Constructor called" RESET << std::endl;
}

AForm& AForm::operator=(const AForm& copy) {
	std::cout << GOLD"[AForm] Copy assignment operator called" RESET << std::endl;
	if (this != &copy)
		this->_isSigned = copy._isSigned;
	return (*this);
}

AForm::~AForm() {
	std::cout << RED"[AForm] Destruct called" RESET << std::endl;
}

std::string	AForm::getName() const {
	return (this->_name);
}

bool	AForm::getIsSigned() const {
	return (this->_isSigned);
}

int	AForm::getGradeToSign() const {
	return (this->_gradeToSign);
}

int	AForm::getGradeToExecute() const {
	return (this->_gradeToExecute);
}

void	AForm::beSigned(const Bureaucrat& bureaucrat) {
	if (bureaucrat.getGrade() > this->_gradeToSign)
		throw AForm::GradeTooLowException();
	this->_isSigned = true;
}

void	AForm::execute(const Bureaucrat& executor) const {
	if (!this->_isSigned)
		throw AForm::FormNotSignedException();
	if (executor.getGrade() > this->_gradeToExecute)
		throw AForm::GradeTooLowException();
	this->executeAction();
}

const char*	AForm::GradeTooHighException::what() const throw() {
	return ("Grade is too high");
}

const char*	AForm::GradeTooLowException::what() const throw() {
	return ("Grade is too low");
}

const char*	AForm::FormNotSignedException::what() const throw() {
	return ("Form is not signed");
}

std::ostream&	operator<<(std::ostream& os, const AForm& form) {
	os << form.getName() << ", form grade to sign: " << form.getGradeToSign()
		<< ", grade to execute: " << form.getGradeToExecute()
		<< ", signed: " << (form.getIsSigned() ? "yes" : "no");
	return (os);
}
