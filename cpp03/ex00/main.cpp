#include <iostream>
#include "ClapTrap.hpp"

int main(){
	ClapTrap huso("badcat");
	ClapTrap hamza;

	hamza = huso;

	huso.attack("a pig");
	hamza.attack("a cat");
	hamza.attack("a pig");
	hamza.takeDamage(5);
	hamza.beRepaired(1);

}