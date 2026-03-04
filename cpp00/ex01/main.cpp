#include <iostream>
#include "Phone.hpp"

int	main()
{
	std::string cmd;
	Phone phoneBook;

	while (true)
	{
		std::cout << "Select Command: (ADD) (SEARCH) (EXIT)" << std::endl;
		if (!std::getline(std::cin, cmd))
		{
			std::cout << "\nEOF detected. Exiting..." << std::endl;
			break;
		}
		if (cmd == "ADD")
			phoneBook.setPhoneBook();
		else if (cmd == "SEARCH")
		{
			phoneBook.getColumn();
			phoneBook.getPhoneBook();
		}
		else if (cmd == "EXIT")
		{
			std::cout << "Goodbye!" << std::endl;
			break;
		}
		else
			std::cout << "Please enter a valid command!!!" << std::endl;
	}
	return (0);
}
