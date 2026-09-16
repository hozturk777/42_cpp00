#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GOLD "\033[38;5;214m"

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	private:
		std::string	_target;
	public:
		PresidentialPardonForm();
		PresidentialPardonForm(const std::string& target);
		PresidentialPardonForm(const PresidentialPardonForm& copy);
		PresidentialPardonForm& operator=(const PresidentialPardonForm& copy);
		~PresidentialPardonForm();

	protected:
		virtual void	executeAction() const;
};

#endif
