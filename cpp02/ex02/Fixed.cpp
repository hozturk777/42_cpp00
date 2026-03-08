#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed() : _num(0){
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int n){
	std::cout << "Int constructor called" << std::endl;
	// 8 bit sola kaydırarak kesirli kısma yer açtık
	this->_num = n << _bits; 
}

Fixed::Fixed(const float f){
	std::cout << "Float constructor called" << std::endl;
	// 42.42 x 256 = 10859.52 (roundf bunu 10860'a yuvarlar)
	this->_num = roundf(f * (1 << _bits));
}

Fixed::Fixed(const Fixed &copy){
	std::cout << "Copy constructor called" << std::endl;
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
    // İki fixed çarpıldığında 2^8 * 2^8 = 2^16 olur. 
    // Bu yüzden float üzerinden çarpıp geri dönmek en güvenli yoldur.
    return Fixed(this->toFloat() * copy.toFloat());
}

Fixed Fixed::operator/(const Fixed &copy) const {
    if (copy.getRawBits() == 0) {
        std::cerr << "Error: Division by zero" << std::endl;
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


// Pre-increment (++a)
Fixed& Fixed::operator++(void) {
    this->_num++;
    return *this;
}

// Post-increment (a++)
Fixed Fixed::operator++(int) {
    Fixed temp(*this);
    this->_num++;
    return temp;
}

// Pre-decrement (--a)
Fixed& Fixed::operator--(void) {
    this->_num--;
    return *this;
}

// Post-decrement (a--)
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