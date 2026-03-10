#include <iostream>
#include "Fixed.hpp"

Fixed::Fixed() : _num(0){
}

Fixed::Fixed(const Fixed &copy){
	*this = copy;
}

Fixed& Fixed::operator=(const Fixed &copy){
	if (this != &copy)
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