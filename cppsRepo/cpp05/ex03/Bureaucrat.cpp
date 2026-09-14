#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include <iostream>
#include <string>

Bureaucrat::Bureaucrat() : _name("Default"), _grade(150) {
    std::cout << GOLD"[Bureaucrat] Default Constructor called" RESET<< std::endl;
}

Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name) {
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade = grade;
	std::cout << GOLD"[Bureaucrat] Parameterized Constructor called" RESET<< std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat& copy) : _name(copy._name), _grade(copy._grade) {
	std::cout << GOLD"[Bureaucrat] Copy Constructor called" RESET<< std::endl;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& copy) {
	std::cout << GOLD"[Bureaucrat] Copy assignment operator called" RESET<< std::endl;
	if (this != &copy)
		this->_grade = copy._grade;
	return *this;
}

Bureaucrat::~Bureaucrat() {
	std::cout << RED"[Bureaucrat] Destruct called" RESET<< std::endl;
}

std::string Bureaucrat::getName() const {
	return (this->_name);
}

int	Bureaucrat::getGrade() const {
	return (this->_grade);
}

void Bureaucrat::incGrade() {
	if (this->_grade <= 1)
		throw Bureaucrat::GradeTooHighException();
	this->_grade--;
}

void Bureaucrat::decGrade() {
	if (this->_grade >= 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade++;
}

void Bureaucrat::signForm(AForm& form) {
	try {
		form.beSigned(*this);
		std::cout << *this << " signed " << form << std::endl;
	} catch (std::exception& e) {
		std::cout << *this << " couldn't sign " << form << " because " << e.what() << "." << std::endl;
	}
}

void Bureaucrat::executeForm(const AForm& form) const {
	try {
		form.execute(*this);
		std::cout << *this << " executed " << form << std::endl;
	} catch (std::exception& e) {
		std::cout << *this << " couldn't execute " << form << " because " << e.what() << "." << std::endl;
	}
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Grade is too high");
}

const char*	Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Grade is too low");
}

std::ostream&	operator<<(std::ostream& os, const Bureaucrat& b)
{
	os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
	return (os);
}