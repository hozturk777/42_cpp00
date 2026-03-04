#include "Harl.hpp"
#include <iostream>

Harl::Harl(){

}
Harl::~Harl(){

}

void Harl::complain (std::string level){
	std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	void (Harl::*functions[])(void) = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};

	size_t i;
	for (i = 0; i < 4; i++)
	{
		if (levels[i] == level)
		{
			break;
		}
	}
	switch (i)
	{
	case 0:
		this->debug();
	case 1:
		this->info();
	case 2:
		this->warning();
	case 3:
		this->error();
		break;
	default:
		std::cout << "Invalid Level" << std::endl;
		break;
	}
}

void Harl::debug (){
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!" << std::endl;
}
void Harl::info (){
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}
void Harl::warning (){
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month." << std::endl;
}
void Harl::error (){
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}