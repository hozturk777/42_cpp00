#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie {
	private:
		std::string _name;
	public:
		std::string getName() const;
		void setName(std::string _name);
		void announce( void );
};

#endif