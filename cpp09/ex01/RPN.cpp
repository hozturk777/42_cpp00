#include "RPN.hpp"
#include <cctype>
#include <climits>
#include <sstream>
#include <stdexcept>

RPN::RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		_stack = other._stack;
	return *this;
}

RPN::~RPN() {}

// Ustteki iki sayiyi alir, islemi yapar, sonucu geri koyar.
// Ilk cikan sagdaki (b), ikinci cikan soldaki (a) operand'dir: a op b
void RPN::applyOperator(char op)
{
	if (_stack.size() < 2)
		throw std::runtime_error("not enough operands");
	long b = _stack.top();
	_stack.pop();
	long a = _stack.top();
	_stack.pop();

	long result;
	if (op == '+')
		result = a + b;
	else if (op == '-')
		result = a - b;
	else if (op == '*')
		result = a * b;
	else
	{
		if (b == 0)
			throw std::runtime_error("division by zero");
		result = a / b;
	}
	// Degerler int araliginda tutulur; boylece bir sonraki carpim long'u tasirmaz
	if (result > INT_MAX || result < INT_MIN)
		throw std::runtime_error("overflow");
	_stack.push(result);
}

long RPN::evaluate(const std::string& expr)
{
	while (!_stack.empty())
		_stack.pop();

	std::istringstream iss(expr);
	std::string token;
	while (iss >> token)
	{
		// Her token tek karakter olmali: 0-9 arasi rakam ya da + - * /
		if (token.size() != 1)
			throw std::runtime_error("invalid token");
		char c = token[0];
		if (std::isdigit(static_cast<unsigned char>(c)))
			_stack.push(c - '0');
		else if (c == '+' || c == '-' || c == '*' || c == '/')
			applyOperator(c);
		else
			throw std::runtime_error("invalid token");
	}
	if (_stack.size() != 1)
		throw std::runtime_error("invalid expression");
	return _stack.top();
}
