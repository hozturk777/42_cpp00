#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie {
	private:
		std::string _name;
	public:
		Zombie(std::string _name);
		~Zombie();
		//std::string getName() const;
		//void setName(std::string _name);
		void announce( void );
};

Zombie* newZombie(std::string _name);
void randomChump( std::string name );

#endif