#include <iostream>
#include "Zombie.hpp"

int main(){
	Zombie* zombies;

	zombies = zombieHorde(3, "Huso");
	for (size_t i = 0; i < 3; i++)
	{
		zombies->announce();
		
	}
	delete[] zombies;	
}