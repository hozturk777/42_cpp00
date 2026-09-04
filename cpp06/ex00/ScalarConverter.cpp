#include "ScalarConverter.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <climits>
#include <cctype>
#include <limits>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &src) { (void)src; }
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &src) { (void)src; return *this; }
ScalarConverter::~ScalarConverter() {}

namespace
{
	enum LiteralType { T_CHAR, T_INT, T_FLOAT, T_DOUBLE, T_INVALID };

	bool isCharLiteral(const std::string &s)
	{
		return (s.size() == 3 && s[0] == '\'' && s[2] == '\'');
	}

	bool isFloatLiteral(const std::string &s)
	{
		if (s.empty() || s[s.size() - 1] != 'f')
			return false;
		std::string body = s.substr(0, s.size() - 1);
		if (body.empty())
			return false;
		std::istringstream iss(body);
		double d;
		iss >> d;
		return (!iss.fail() && iss.eof());
	}

	bool isDoubleLiteral(const std::string &s)
	{
		if (s.empty())
			return false;
		std::istringstream iss(s);
		double d;
		iss >> d;
		return (!iss.fail() && iss.eof());
	}

	LiteralType detect(const std::string &s)
	{
		if (isCharLiteral(s))
			return T_CHAR;
		if (s == "nanf" || s == "+inff" || s == "-inff")
			return T_FLOAT;
		if (s == "nan" || s == "+inf" || s == "-inf")
			return T_DOUBLE;
		if (isFloatLiteral(s))
			return T_FLOAT;
		if (isDoubleLiteral(s))
			return (s.find('.') != std::string::npos) ? T_DOUBLE : T_INT;
		return T_INVALID;
	}

	void printChar(double d)
	{
		if (std::isnan(d) || std::isinf(d) || d < CHAR_MIN || d > CHAR_MAX)
			std::cout << "char: impossible" << std::endl;
		else
		{
			char c = static_cast<char>(d);
			if (std::isprint(static_cast<unsigned char>(c)))
				std::cout << "char: '" << c << "'" << std::endl;
			else
				std::cout << "char: Non displayable" << std::endl;
		}
	}

	void printInt(double d)
	{
		if (std::isnan(d) || std::isinf(d) || d < INT_MIN || d > INT_MAX)
			std::cout << "int: impossible" << std::endl;
		else
			std::cout << "int: " << static_cast<int>(d) << std::endl;
	}

	std::string withDecimalPoint(double value)
	{
		std::ostringstream oss;
		oss << value;
		std::string s = oss.str();
		if (s.find('.') == std::string::npos && s.find('e') == std::string::npos
			&& s.find('E') == std::string::npos)
			s += ".0";
		return s;
	}

	void printFloat(double d)
	{
		if (std::isnan(d))
			std::cout << "float: nanf" << std::endl;
		else if (std::isinf(d))
			std::cout << "float: " << (d > 0 ? "+inff" : "-inff") << std::endl;
		else
			std::cout << "float: " << withDecimalPoint(static_cast<float>(d)) << "f" << std::endl;
	}

	void printDouble(double d)
	{
		if (std::isnan(d))
			std::cout << "double: nan" << std::endl;
		else if (std::isinf(d))
			std::cout << "double: " << (d > 0 ? "+inf" : "-inf") << std::endl;
		else
			std::cout << "double: " << withDecimalPoint(d) << std::endl;
	}
}

void ScalarConverter::convert(const std::string &literal)
{
	LiteralType type = detect(literal);
	double d = 0;

	if (type == T_INVALID)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	else if (type == T_CHAR)
		d = static_cast<double>(literal[1]);
	else if (literal == "nan" || literal == "nanf")
		d = std::numeric_limits<double>::quiet_NaN();
	else if (literal == "+inf" || literal == "+inff")
		d = std::numeric_limits<double>::infinity();
	else if (literal == "-inf" || literal == "-inff")
		d = -std::numeric_limits<double>::infinity();
	else
	{
		std::string body = (type == T_FLOAT) ? literal.substr(0, literal.size() - 1) : literal;
		std::istringstream iss(body);
		iss >> d;
	}
	printChar(d);
	printInt(d);
	printFloat(d);
	printDouble(d);
}
