#include "Brain.hpp"
#include <iostream>

Brain::Brain() {
    std::cout << "Brain Default Constructor called" << std::endl;
	for (size_t i = 0; i < 100; i++)
	{
		this->ideas[i] = "Brainzzz";
	}
}

Brain::Brain(const Brain& copy) {
    std::cout << "Brain Copy Constructor called" << std::endl;
    *this = copy;
}

Brain& Brain::operator=(const Brain& copy) {
    std::cout << "Brain Assignment Operator called" << std::endl;
    if (this != &copy) {
        for (int i = 0; i < 100; i++) {
            this->ideas[i] = copy.ideas[i];
        }
    }
    return *this;
}

Brain::~Brain() {
    std::cout << "Brain Destructor called" << std::endl;
}