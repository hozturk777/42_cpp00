#include <iostream>
#include <string>
#include <iomanip>
#include "Contact.hpp"

int	main()
{
	std::string name;
	std::string surName;
	std::string cmd;
	Contact person;

	std::cout << "Select Command: (ADD) (SEARCH) (EXIT)" << std::endl;
	std::getline(std::cin, cmd);
	if (cmd == "ADD")
	{
		std::cout << "Name: ";
		std::getline(std::cin, name);

		std::cout << "surName: ";
		std::getline(std::cin, surName);
	}
	person.setFirstName(name);
	person.setSurName(surName);

	std::cout << "|" << std::setw(10) << person.getFirstName();
	std::cout << "|" << std::setw(10) << person.getSurName();
	std::cout << "|" << std::endl;
}
