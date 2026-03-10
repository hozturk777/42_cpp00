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

bool Fixed::operator>(const Fixed &copy) const { return this->_num > copy.getRawBits(); }
bool Fixed::operator<(const Fixed &copy) const { return this->_num < copy.getRawBits(); }
bool Fixed::operator>=(const Fixed &copy) const { return this->_num >= copy.getRawBits(); }
bool Fixed::operator<=(const Fixed &copy) const { return this->_num <= copy.getRawBits(); }
bool Fixed::operator==(const Fixed &copy) const { return this->_num == copy.getRawBits(); }
bool Fixed::operator!=(const Fixed &copy) const { return this->_num != copy.getRawBits(); }

Fixed Fixed::operator+(const Fixed &copy) const {
    return Fixed(this->toFloat() + copy.toFloat());
}

Fixed Fixed::operator-(const Fixed &copy) const {
    return Fixed(this->toFloat() - copy.toFloat());
}

Fixed Fixed::operator*(const Fixed &copy) const {
    return Fixed(this->toFloat() * copy.toFloat());
}

Fixed Fixed::operator/(const Fixed &copy) const {
    if (copy.getRawBits() == 0) {
        std::cout << "Error: Division by zero" << std::endl;
        return Fixed(0);
    }
    return Fixed(this->toFloat() / copy.toFloat());
}

Fixed& Fixed::operator=(const Fixed &copy){
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &copy)
		this->_num = copy.getRawBits();
	return *this;
}


Fixed& Fixed::operator++(void) {
    this->_num++;
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed temp(*this);
    this->_num++;
    return temp;
}

Fixed& Fixed::operator--(void) {
    this->_num--;
    return *this;
}

Fixed Fixed::operator--(int) {
    Fixed temp(*this);
    this->_num--;
    return temp;
}

Fixed& Fixed::min(Fixed &a, Fixed &b) {
    return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed &a, const Fixed &b) {
    return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed &a, Fixed &b) {
    return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed &a, const Fixed &b) {
    return (a > b) ? a : b;
}