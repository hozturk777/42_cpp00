#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <string>
#define GREEN "\033[1;32m"
#define RESET "\033[0m"
#define BLUE "\033[1;34m"
#define RED "\033[1;31m"
#define GOLD "\033[38;5;214m"

class WrongAnimal {
	protected:
		std::string _type;
	public:
		WrongAnimal();
		WrongAnimal(const WrongAnimal& copy);
		WrongAnimal& operator=(const WrongAnimal& copy);
		~WrongAnimal();

		void makeSound() const;
    	std::string getType() const;
};

#endif