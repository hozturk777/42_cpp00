#include "Dog.hpp"
#include <iostream>

Dog::Dog() {
	this->_type = "Dog";
	this->_brain = new Brain();
    std::cout << GOLD"[Dog] Default Constructor called" RESET<< std::endl;
}

Dog::Dog(const Dog& copy) : Animal(copy) {
    std::cout << GOLD"[Dog] Copy Constructor called" RESET<< std::endl;
	this->_brain = new Brain(*(copy._brain));
}

Dog& Dog::operator=(const Dog& copy) {
	std::cout << GOLD"[Dog] Copy assignment operator called" RESET<< std::endl;
    if (this != &copy) {
        this->_type = copy._type;
		if (this->_brain)
			delete this->_brain;	
		if (copy._brain)
            this->_brain = new Brain(*(copy._brain));
        else
            this->_brain = NULL;
    }
    return *this;
}

Dog::~Dog() {
	delete this->_brain;
	std::cout << RED"Dog Destructor called" RESET << std::endl;
}

void Dog::makeSound() const {
    std::cout << GREEN"[Dog]: Woof! Woof! 🐶" RESET<< std::endl;
}