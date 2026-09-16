#ifndef INTERN_HPP
#define INTERN_HPP

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GOLD "\033[38;5;214m"

#include <string>

class AForm;

class Intern
{
	public:
		Intern();
		Intern(const Intern& copy);
		Intern& operator=(const Intern& copy);
		~Intern();

		AForm*	makeForm(const std::string& formName, const std::string& target) const;

	private:
		static AForm*	createShrubbery(const std::string& target);
		static AForm*	createRobotomy(const std::string& target);
		static AForm*	createPardon(const std::string& target);
};

#endif
