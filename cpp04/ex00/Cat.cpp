#include "Cat.hpp"
#include <iostream>

Cat::Cat() {
	this->_type = "Cat";
    std::cout << GOLD"[Cat] Default Constructor called" RESET<< std::endl;
}

Cat::Cat(const Cat& copy) : Animal(copy) {
    std::cout << GOLD"[Cat] Copy Constructor called" RESET<< std::endl;
}

Cat& Cat::operator=(const Cat& copy) {
	std::cout << GOLD"[Cat] Copy assignment operator called" RESET<< std::endl;
    if (this != &copy) {
        this->_type = copy._type;
    }
    return *this;
}

Cat::~Cat() {
	std::cout << RED"Cat Destructor called" RESET << std::endl;
}

void Cat::makeSound() const {
    std::cout << GREEN"[Cat]: Meow! Meow! 🐱" RESET<< std::endl;
}
