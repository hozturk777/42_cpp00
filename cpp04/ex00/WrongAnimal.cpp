#include "WrongAnimal.hpp"
#include <iostream>

WrongAnimal::WrongAnimal() : _type("WrongAnimal") {
    std::cout << GOLD"[WrongAnimal] Default Constructor called" RESET<< std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& copy) {
    std::cout << GOLD"[WrongAnimal] Copy Constructor called" RESET<< std::endl;
    *this = copy;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& copy) {
	std::cout << GOLD"[WrongAnimal] Copy assignment operator called" RESET<< std::endl;
    if (this != &copy) {
        this->_type = copy._type;
    }
    return *this;
}
WrongAnimal::~WrongAnimal() {
	std::cout << RED"WrongAnimal Destructor called" RESET << std::endl;
}

void WrongAnimal::makeSound() const {
    std::cout << GREEN"[WrongAnimal] makes a weird, unrecognizable sound" RESET<< std::endl;
}

std::string WrongAnimal::getType() const {
    return this->_type;
}