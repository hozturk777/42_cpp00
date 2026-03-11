#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap() : _name("huozturk"), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << GREEN"Default constructor called" RESET<< std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << GREEN"Constructor with name called" RESET<< std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &copy) {
	std::cout << GREEN"Copy constructor called" RESET<< std::endl;
	*this = copy;
}

ClapTrap& ClapTrap::operator=(const ClapTrap &copy)
{
	std::cout << GREEN"Copy assignment operator called" RESET<< std::endl;
	if (this != &copy)
	{
		this->_name = copy._name;
		this->_hitPoints = copy._hitPoints;
		this->_energyPoints = copy._energyPoints;
		this->_attackDamage = copy._attackDamage;
	}
	return *this;
}

ClapTrap::~ClapTrap(){
	std::cout << RED"Destructor called" RESET << std::endl;
}

void ClapTrap::attack(const std::string& target) {
    if (this->_hitPoints <= 0 || this->_energyPoints <= 0) {
        std::cout << RED"ClapTrap " << this->_name << " is out of juice/HP and can't attack!" RESET<< std::endl;
        return;
    }
	else
	{
		this->_energyPoints--;
		std::cout << BLUE"ClapTrap " <<this->_name << " attacks " << target << ", causing " << this->_attackDamage << " points of damage!" RESET<< std::endl;
	}
}

void ClapTrap::takeDamage(unsigned int amount) {
	if (this->_hitPoints <= 0)
	{
		std::cout << RED << "ClapTrap " << this->_name << " is already dead! Stop hitting it!" << RESET << std::endl;	}
	else
	{
		this->_hitPoints -= amount;
		std::cout << RED"ClapTrap " << this->_name << " takes " << amount << " damage! HP left: " RESET<< this->_hitPoints << std::endl;
	}
}

void ClapTrap::beRepaired(unsigned int amount){
	if (this->_hitPoints > 0 && this->_energyPoints > 0)
	{
		std::cout << BLUE"ClapTrap " << this->_name << " restores " << amount << " HP" RESET << std::endl;
		this->_hitPoints += amount;
		this->_energyPoints--;
		std::cout << BLUE"Remaning HP: " RESET<< this->_hitPoints << std::endl;
	}
	else if (this->_energyPoints > 0)
	{
		std::cout << RED"ClapTrap " << this->_name << " is dead and cannot be restored." RESET<< std::endl;
	}
	else {
        std::cout << RED"ClapTrap " << _name << " has no energy left to repair!" RESET<< std::endl;
    }
}