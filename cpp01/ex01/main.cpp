#include <iostream>
#include "Zombie.hpp"

int main(){
	Zombie* zombies;

	zombies = zombieHorde(1, "Huso");
	if (!zombies)
	{
		std::cout << "Error" << std::endl;
		return (1);
	}
	
	for (size_t i = 0; i < 3; i++)
	{
		zombies->announce();
	}
	delete[] zombies;
	return (0);	
}