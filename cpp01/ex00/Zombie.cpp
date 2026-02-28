#include "Zombie.hpp"

#include <iostream>

std::string Zombie::getName() const
{
	return (this->_name);
}

void Zombie::setName(std::string _name)
{
	this->_name = _name;
}

void Zombie::announce( void )
{
	std::cout << this->_name << "BraiiiiiiinnnzzzZ..." << std::endl;
}