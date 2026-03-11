#include "FragTrap.hpp"
#include <iostream>

FragTrap::FragTrap() : ClapTrap()
{
	std::cout << GREEN"FragTrap Default constructor called" RESET<< std::endl;

	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	std::cout << GREEN"FragTrap Constructor with name called" RESET<< std::endl;

	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
}

FragTrap::FragTrap(const FragTrap &copy) : ClapTrap(copy)
{
	std::cout << GREEN"FragTrap Copy constructor called" RESET<< std::endl;
	*this = copy;
}

FragTrap& FragTrap::operator=(const FragTrap &copy)
{
	std::cout << GREEN"FragTrap Copy assignment operator called" RESET<< std::endl;
	if (this != &copy)
	{
		this->_name = copy._name;
		this->_hitPoints = copy._hitPoints;
		this->_energyPoints = copy._energyPoints;
		this->_attackDamage = copy._attackDamage;
	}
	return *this;	
}

FragTrap::~FragTrap(){
	std::cout << RED"FragTrap Destructor called For: " BLUE<< this->_name << RESET<< std::endl;
}

void FragTrap::highFivesGuys(void)
{
	if (this->_hitPoints <= 0)
		std::cout << "FragTrap " << this->_name << " is too damaged to high five..." << std::endl;
	else
		std::cout << "FragTrap " << this->_name << " says: \"High fives, guys! Don't leave me hanging!\" ✋" << std::endl;
}