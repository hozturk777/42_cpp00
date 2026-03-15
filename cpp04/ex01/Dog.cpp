#include "Dog.hpp"
#include <iostream>

Dog::Dog() {
    std::cout << GOLD"[Dog] Default Constructor called" RESET<< std::endl;
}

Dog::Dog(const Dog& copy) : Animal(copy) {
    std::cout << GOLD"[Dog] Copy Constructor called" RESET<< std::endl;
}

Dog& Dog::operator=(const Dog& copy) {
	std::cout << GOLD"[Dog] Copy assignment operator called" RESET<< std::endl;
    if (this != &copy) {
        this->_type = copy._type;
    }
    return *this;
}

Dog::~Dog() {
	std::cout << RED"Dog Destructor called" RESET << std::endl;
}

void Dog::makeSound() const {
    std::cout << GREEN"[Dog]: Woof! Woof! 🐶" RESET<< std::endl;
}
