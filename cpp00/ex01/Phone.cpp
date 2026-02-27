#include "Phone.hpp"
#include <iostream>
#include <iomanip>
#include "Column.hpp"

Phone::Phone()
{}

Phone::~Phone()
{}


void	Phone::getPhoneBook() // stream insertion(<<) overloading ederek yazdırılacak
{
	std::cout << "|" << Column("index");
	std::cout << "|" << Column("FirstName");
	std::cout << "|" << Column("Surname");
	std::cout << "|" << Column("PhoneNumber");
	std::cout << "|" << std::endl;

	// std::cout << "|" << std::setw(10) << "index";
	// std::cout << "|" << std::setw(10) << "FirstName";
	// std::cout << "|" << std::setw(10) << "SurName";
	// std::cout << "|" << std::setw(10) << "PhoneNumber";
	// std::cout << "|" << std::setw(10) << "DarkestSecret";
	// std::cout << "|" << std::endl;



}