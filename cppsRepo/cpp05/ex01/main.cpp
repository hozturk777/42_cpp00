#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
	std::cout << "----- Bureaucrat OCF -----" << std::endl;
	Bureaucrat huso("Huso", 42);
	Bureaucrat copy(huso);
	Bureaucrat assigned = huso;
	std::cout << huso << std::endl;
	std::cout << copy << std::endl;
	std::cout << assigned << std::endl;

	std::cout << "----- Form olusturma ve yazdirma -----" << std::endl;
	Form form("EasyForm", 140, 140);
	std::cout << form << std::endl;

	std::cout << "----- signForm basarili -----" << std::endl;
	Bureaucrat highGrade("Boss", 1);
	highGrade.signForm(form);
	std::cout << form << std::endl;

	std::cout << "----- signForm basarisiz (grade yetersiz) -----" << std::endl;
	Bureaucrat lowGrade("Newbie", 145);
	Form otherForm("OtherForm", 100, 100);
	lowGrade.signForm(otherForm);

	std::cout << "----- Bureaucrat gecersiz grade -----" << std::endl;
	try {
		Bureaucrat invalid("Invalid", 0);
		(void)invalid;
	} catch (std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}

	std::cout << "----- Form gecersiz grade -----" << std::endl;
	try {
		Form badForm("BadForm", 151, 5);
		(void)badForm;
	} catch (std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
}
