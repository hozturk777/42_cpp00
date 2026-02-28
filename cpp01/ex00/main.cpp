#include "Zombie.hpp"


int main()
{
	Zombie z("Huso");

	z.announce();

	Zombie* news = newZombie("FALAN");
	news->announce();
	delete(news);

	randomChump("Random");

	return (0);
}