#include <iostream>
#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap() 
{
	std::cout << GREEN"ScavTrap Default constructor called" RESET<< std::endl;

	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	std::cout << GREEN"ScavTrap Constructor with name called" RESET<< std::endl;

	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
}

ScavTrap::ScavTrap(const ScavTrap &copy) : ClapTrap(copy)
{
	std::cout << GREEN"ScavTrap Copy constructor called" RESET<< std::endl;
	*this = copy;
}

ScavTrap& ScavTrap::operator=(const ScavTrap &copy)
{
	std::cout << GREEN"ScavTrap Copy assignment operator called" RESET<< std::endl;
	if (this != &copy)
	{
		this->_name = copy._name;
		this->_hitPoints = copy._hitPoints;
		this->_energyPoints = copy._energyPoints;
		this->_attackDamage = copy._attackDamage;
	}
	return *this;
}

ScavTrap::~ScavTrap(){
	std::cout << RED"ScavTrap Destructor called" RESET << std::endl;
}

void ScavTrap::attack(const std::string& target) {
    if (this->_hitPoints == 0 || this->_energyPoints == 0) {
        std::cout << RED"ScavTrap " << this->_name << " is out of juice/HP and can't attack!" RESET<< std::endl;
    }
	else
	{
		this->_energyPoints--;
		std::cout << BLUE"ScavTrap " <<this->_name << " attacks " << target << ", causing " << this->_attackDamage << " points of damage!" RESET<< std::endl;
	}
}

void ScavTrap::guardGate(){
	if (this->_hitPoints <= 0 || this->_energyPoints <= 0)
	{
		std::cout << RED"ScavTrap " << this->_name << " has no life or energy left to perform this task." RESET<< std::endl;
	}
	else
	{
		std::cout << RED"ScavTrap " << this->_name << " is now in Gate keeper mode. None shall pass!" RESET<< std::endl;
	}
}
