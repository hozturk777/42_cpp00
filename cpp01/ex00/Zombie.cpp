#include "Zombie.hpp"

#include <iostream>

Zombie::Zombie()
{
}

Zombie::Zombie(std::string _name)
{
	this->_name = _name;
}
Zombie::~Zombie()
{
    std::cout << this->_name << ": has been destroyed." << std::endl;
}

void Zombie::announce( void )
{
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}