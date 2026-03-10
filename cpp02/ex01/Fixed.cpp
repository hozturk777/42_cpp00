#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed() : _num(0){
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int n){
	std::cout << "Int constructor called" << std::endl;
	this->_num = n << _bits; 
}

Fixed::Fixed(const float f){
	std::cout << "Float constructor called" << std::endl;
	this->_num = roundf(f * (1 << _bits));
}

Fixed::Fixed(const Fixed &copy){
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

Fixed& Fixed::operator=(const Fixed &copy){
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &copy)
		this->_num = copy.getRawBits();
	return *this;
}

Fixed::~Fixed(){
	std::cout << "Destructor called" << std::endl;
}

float Fixed::toFloat(void) const {
	return ((float)this->_num / (1 << _bits));
}

int Fixed::toInt(void) const {
	return (this->_num >> _bits);
}

int Fixed::getRawBits(void) const {
	std::cout << "getRawBits member function called" << std::endl;
    return this->_num;
}

void Fixed::setRawBits(int const raw) {
    this->_num = raw;
}

std::ostream& operator<<(std::ostream& os, const Fixed& obj){
	os << obj.toFloat();
	return (os);
}
