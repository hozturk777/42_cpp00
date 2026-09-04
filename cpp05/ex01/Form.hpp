#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <exception>
#include <iostream>

class Bureaucrat; // Incomplete type nesne oluşturamaz ve attributelere ulaşamazsın

class Form
{
	private:
		const std::string	_name;
		bool				_isSigned;
		const int			_gradeToSign; // Formu imzalamak için min yetki
		const int			_gradeToExecute; // Formu execute edebilmek için min yetki
	public:
		Form();
		Form(const std::string& name, int gradeToSign, int gradeToExecute);
		Form(const Form& copy);
		Form& operator=(const Form& copy);
		~Form();

		std::string	getName() const;
		bool		getIsSigned() const;
		int			getGradeToSign() const;
		int			getGradeToExecute() const;

		void	beSigned(const Bureaucrat& bureaucrat);

		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw();
		};

		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

std::ostream&	operator<<(std::ostream& os, const Form& form);

#endif
