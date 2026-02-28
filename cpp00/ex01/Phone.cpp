#include "Phone.hpp"
#include <iostream>
#include <iomanip>
#include "Column.hpp"

Phone::Phone()
{
	_totalPerson = 0;
	_index = 0;
}

Phone::~Phone()
{}


void Phone::getColumn() // stream insertion(<<) overloading ederek yazdırılacak
{
	std::cout << "|" << Column("index");
	std::cout << "|" << Column("Name");
	std::cout << "|" << Column("Surname");
	std::cout << "|" << Column("NickName");
	std::cout << "|" << std::endl;
}

void Phone::getPhoneBook()
{
	std::string	inp;
	int	i;

	for (size_t i = 0; i < this->_totalPerson; i++)
	{
		std::cout << "|" << std::setw(10) << i + 1;
		std::cout << "|" << Column(this->_person[i].getFirstName());
		std::cout << "|" << Column(this->_person[i].getSurName());
		std::cout << "|" << Column(this->_person[i].getNickName());
		std::cout << "|" << std::endl;
	}

	std::cout << "Please enter the index number of the person whose information you wish to view." << std::endl;
	std::cout << "> ";
	std:getline(std::cin, inp);
	i = inp[0] - '1';
	if (i >= 0 && i <= 9)
	{
		std::cout << "----------------------" << std::endl;
		std::cout << "Index: " << i + 1 << std::endl;
		std::cout << "FirstName: " << this->_person[i].getFirstName() << std::endl;
		std::cout << "SurName: " << this->_person[i].getSurName() << std::endl;
		std::cout << "NickName: " << this->_person[i].getNickName() << std::endl;
		std::cout << "PhoneNumber: " << this->_person[i].getPhoneNumber() << std::endl;
		std::cout << "DarkestSecret: " << this->_person[i].getDarkestSecret() << std::endl;
		std::cout << "----------------------" << std::endl;
		//std::cout << "|" << std::endl;
	}
	else
	{
		std::cout << "FAIL" << std::endl;
	}
}

void Phone::setPhoneBook()
{
	std::string name;
	std::string surName;
	std::string nickName;
	std::string phoneNumber;
	std::string darkestSecret;

	while (true)
	{
		std::cout << "Name: ";
		if (!std::getline(std::cin, name))
			return;
		if (!name.empty())
			break;	
		std::cout << "Please enter a valid value" << std::endl;
	}
	while (true)
	{
		std::cout << "surName: ";
		if (!std::getline(std::cin, surName))
			return;
		if (!surName.empty())
			break;
		std::cout << "Please enter a valid value" << std::endl;
	}
	while (true)
	{
		std::cout << "NickName: ";
		if (!std::getline(std::cin, nickName))
			return ;
		if (!nickName.empty())
			break;
		std::cout << "Please enter a valid value" << std::endl;
	}
	while (true)
	{
		std::cout << "Phone Number: ";
		if (!std::getline(std::cin, phoneNumber))
			return;
		if (!phoneNumber.empty())
			break;
		std::cout << "Please enter a valid value" << std::endl;
	}
	while (true)
	{
		std::cout << "Darkest Secret: ";
		if (!std::getline(std::cin, darkestSecret))
			return;
		if (!darkestSecret.empty())
			break;
		std::cout << "Please enter a valid value" << std::endl;
	}
	this->_person[_index].setFirstName(name);
	this->_person[_index].setSurName(surName);
	this->_person[_index].setNickName(nickName);
	this->_person[_index].setPhoneNumber(phoneNumber);
	this->_person[_index].setDarkestSecret(darkestSecret);

	this->_index = (this->_index + 1) % 8;
	if (this->_totalPerson < 8)
		this->_totalPerson += 1;
}