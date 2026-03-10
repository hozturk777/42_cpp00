#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed() : _num(0){
}

Fixed::Fixed(const int n){
	this->_num = n << _bits; 
}

Fixed::Fixed(const float f){
	this->_num = roundf(f * (1 << _bits));
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

float Fixed::toFloat(void) const {
	return ((float)this->_num / (1 << _bits));
}

int Fixed::toInt(void) const {
	return (this->_num >> _bits);
}

int Fixed::getRawBits(void) const {
    return this->_num;
}

void Fixed::setRawBits(int const raw) {
    this->_num = raw;
}

std::ostream& operator<<(std::ostream& os, const Fixed& obj){
	os << obj.toFloat();
	return (os);
}
