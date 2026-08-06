#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#define GREEN "\033[1;32m"
#define RESET "\033[0m"
#define BLUE "\033[1;34m"
#define RED "\033[1;31m"
#define GOLD "\033[38;5;214m"

#include <string>
#include <exception>

class Form;

class Bureaucrat
{
	private:
		const std::string	_name;
		int					_grade;
	public:
		Bureaucrat();
		Bureaucrat(const std::string& name, int grade); // Name'in ref olma sebebi const olduğu için gereksiz değişken oluşturmamak için
		Bureaucrat(const Bureaucrat& copy);
		Bureaucrat& operator=(const Bureaucrat& copy);
		~Bureaucrat();

		std::string	getName() const;
		int	getGrade() const;
		void incGrade();
		void decGrade();
		void signForm(Form& form);

		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw(); // What:Dynamic dispatch
		}; // Nested class

		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw();
		}; // Nested class

};

std::ostream&	operator<<(std::ostream& os, const Bureaucrat& b);

#endif