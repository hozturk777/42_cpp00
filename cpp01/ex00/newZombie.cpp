#include "Zombie.hpp"
#include <iostream>

Zombie* newZombie(std::string _name)
{
	Zombie* new_Zombie = new Zombie(_name);

	return(new_Zombie);
}