#include <iostream>
#include "WrongCat.hpp"

WrongCat::WrongCat(){
    std::cout << GOLD"[WrongCat] Default Constructor called" RESET<< std::endl;
}

WrongCat::WrongCat(const WrongCat& copy) : WrongAnimal(copy) {
    std::cout << GOLD"[WrongCat] Copy Constructor called" RESET<< std::endl;
    *this = copy;
}

WrongCat& WrongCat::operator=(const WrongCat& copy) {
	std::cout << GOLD"[WrongCat] Copy assignment operator called" RESET<< std::endl;
    if (this != &copy) {
        this->_type = copy._type;
    }
    return *this;
}
WrongCat::~WrongCat() {
	std::cout << RED"WrongCat Destructor called" RESET << std::endl;
}

void WrongCat::makeSound() const {
    std::cout << GREEN"[WrongCat]: Meow! Meow! 🐱" RESET<< std::endl;
}
