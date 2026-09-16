#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GOLD "\033[38;5;214m"

#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
	private:
		std::string	_target;
	public:
		RobotomyRequestForm();
		RobotomyRequestForm(const std::string& target);
		RobotomyRequestForm(const RobotomyRequestForm& copy);
		RobotomyRequestForm& operator=(const RobotomyRequestForm& copy);
		~RobotomyRequestForm();

	protected:
		virtual void	executeAction() const;
};

#endif
