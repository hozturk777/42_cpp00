#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#define GREEN "\033[1;32m"
#define RESET "\033[0m"
#define BLUE "\033[1;34m"
#define RED "\033[1;31m"

#include <string>

class ClapTrap{
	private:
		std::string _name;
		unsigned int _hitPoints;
		unsigned int _energyPoints;
		unsigned int _attackDamage;
	public:
		ClapTrap();
        ClapTrap(std::string name); 
        ClapTrap(const ClapTrap &copy);
        ClapTrap &operator=(const ClapTrap &copy);
        ~ClapTrap();

		void attack(const std::string& target);
		void takeDamage(int amount);
		void beRepaired(int amount);
};

#endif