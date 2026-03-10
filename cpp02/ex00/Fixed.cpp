#include <iostream>
#include "Fixed.hpp"

Fixed::Fixed() : _num(0){
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &copy){
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

Fixed& Fixed::operator=(const Fixed &copy){
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &copy) // Olmadığı durumda a = a durumunda atama yapmadan a verisi siliniyor veri çöpe gidiyor
		this->_num = copy.getRawBits();
	return *this;
}

Fixed::~Fixed(){
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const {
    std::cout << "getRawBits member function called" << std::endl;
    return this->_num;
}

void Fixed::setRawBits(int const raw) {
    this->_num = raw;
}