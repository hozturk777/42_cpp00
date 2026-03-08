#ifndef FIXED_HPP
#define FIXED_HPP

#include <ostream>

class Fixed
{
	private:	
		int					_num;
		static const int	_bits = 8;
	public:
		Fixed();
		Fixed(const int n);
		Fixed(const float f);
		Fixed(const Fixed &copy);
		Fixed& operator=(const Fixed &copy);
		~Fixed();

		int getRawBits( void ) const;
		void setRawBits( int const raw );
		float toFloat( void ) const;
		int toInt( void ) const;

		bool    operator>(const Fixed &copy) const;
		bool    operator<(const Fixed &copy) const;
		bool    operator>=(const Fixed &copy) const;
		bool    operator<=(const Fixed &copy) const;
		bool    operator==(const Fixed &copy) const;
		bool    operator!=(const Fixed &copy) const;

		Fixed   operator+(const Fixed &copy) const;
		Fixed   operator-(const Fixed &copy) const;
		Fixed   operator*(const Fixed &copy) const;
		Fixed   operator/(const Fixed &copy) const;

		Fixed&  operator++(void);       // ++pre
		Fixed   operator++(int);        // post++
		Fixed&  operator--(void);       // --pre
		Fixed   operator--(int);        // post--

		static Fixed& min(Fixed &a, Fixed &b);
		static const Fixed& min(const Fixed &a, const Fixed &b);
		static Fixed& max(Fixed &a, Fixed &b);
		static const Fixed& max(const Fixed &a, const Fixed &b);
};

std::ostream& operator<<(std::ostream& os, const Fixed& obj);



#endif