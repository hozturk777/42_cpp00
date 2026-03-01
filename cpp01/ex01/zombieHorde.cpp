#include "Zombie.hpp"
#include <iostream>

Zombie* zombieHorde( int N, std::string name )
{
	Zombie* horde = new Zombie[N];

	for (size_t i = 0; i < N; i++)
	{
		horde[i].setName(name);
	}
	return (horde);
}