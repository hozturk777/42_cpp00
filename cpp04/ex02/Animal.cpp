#include "Animal.hpp"
#include <iostream>

Animal::Animal() : _type("Animal") {
    std::cout << GOLD"[Animal] Default Constructor called" RESET<< std::endl;
}

Animal::Animal(const Animal& copy) {
    std::cout << GOLD"[Animal] Copy Constructor called" RESET<< std::endl;
    *this = copy;
}

Animal& Animal::operator=(const Animal& copy) {
	std::cout << GOLD"[Animal] Copy assignment operator called" RESET<< std::endl;
    if (this != &copy) {
        this->_type = copy._type;
    }
    return *this;
}

Animal::~Animal() {
	std::cout << RED"Animal Destructor called" RESET << std::endl;
}

void Animal::makeSound() const {
    std::cout << GREEN"[Animal] makes a weird, unrecognizable sound" RESET<< std::endl;
}

std::string Animal::getType() const {
    return this->_type;
}