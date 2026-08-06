#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
	Bureaucrat huso("Huso", 112);
	Bureaucrat memo = huso;
	Bureaucrat femo(memo);
	memo.decGrade();
	femo.incGrade();
	std::cout << huso << std::endl;
	std::cout << memo << std::endl;
	std::cout << femo << std::endl;

	std::cout << "----- Form tests -----" << std::endl;

	Form easyForm("EasyForm", 140, 140);
	Bureaucrat lowGrade("Newbie", 145);
	Bureaucrat highGrade("Boss", 1);

	lowGrade.signForm(easyForm);
	std::cout << easyForm << std::endl;

	highGrade.signForm(easyForm);
	std::cout << easyForm << std::endl;

	try {
		Form badForm("BadForm", 0, 5);
	} catch (std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
}