#include "Cat.hpp"
#include <iostream>

Cat::Cat() {
	this->_type = "Cat";
	this->_brain = new Brain();
    std::cout << GOLD"[Cat] Default Constructor called" RESET<< std::endl;
}

Cat::Cat(const Cat& copy) : Animal(copy) {
    std::cout << GOLD"[Cat] Copy Constructor called" RESET<< std::endl;
	this->_brain = new Brain(*(copy._brain));
}

Cat& Cat::operator=(const Cat& copy) {
	std::cout << GOLD"[Cat] Copy assignment operator called" RESET<< std::endl;
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

Cat::~Cat() {
	delete this->_brain;
	std::cout << RED"Cat Destructor called" RESET << std::endl;
}

void Cat::makeSound() const {
    std::cout << GREEN"[Cat]: Meow! Meow! 🐱" RESET<< std::endl;
}
