#include <iostream>
#include "Fixed.hpp"
int main( void ) {
	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;
	//return 0;

	//Fixed a(2.5f);    
    //Fixed b(4.25f);    
    //Fixed c;          

    //c = a + b; 

    //std::cout << "A degeri: " << a << std::endl;
    //std::cout << "B degeri: " << b << std::endl;
    //std::cout << "Toplam (C): " << c << std::endl;

    return 0;
}