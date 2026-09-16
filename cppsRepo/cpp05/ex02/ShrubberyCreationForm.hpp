#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GOLD "\033[38;5;214m"

#include "AForm.hpp"

class ShrubberyCreationForm : public AForm
{
	private:
		std::string	_target;
	public:
		ShrubberyCreationForm();
		ShrubberyCreationForm(const std::string& target);
		ShrubberyCreationForm(const ShrubberyCreationForm& copy);
		ShrubberyCreationForm& operator=(const ShrubberyCreationForm& copy);
		~ShrubberyCreationForm();

	protected:
		virtual void	executeAction() const;
};

#endif
