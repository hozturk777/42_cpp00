#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie {
	private:
		std::string _name;
	public:
		Zombie();
		~Zombie();
		void setName(std::string _name);
		void announce( void );
};

Zombie* zombieHorde( int N, std::string name );

#endif