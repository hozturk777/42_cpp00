#include "PmergeMe.hpp"
#include <cctype>
#include <climits>
#include <sstream>
#include <stdexcept>
#include <string>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

const std::vector<int>& PmergeMe::getVector() const { return _vec; }

const std::deque<int>& PmergeMe::getDeque() const { return _deq; }

// Sadece rakamlardan olusan, 1 ile INT_MAX arasindaki sayiyi kabul eder
static int parseNumber(const std::string& token)
{
	if (token.empty())
		throw std::runtime_error("empty number");
	long value = 0;
	for (std::string::size_type i = 0; i < token.size(); ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(token[i])))
			throw std::runtime_error("not a positive integer");
		value = value * 10 + (token[i] - '0');
		if (value > INT_MAX)
			throw std::runtime_error("number too large");
	}
	if (value == 0)
		throw std::runtime_error("not a positive integer");
	return static_cast<int>(value);
}

void PmergeMe::loadVector(int argc, char** argv)
{
	_vec.clear();
	for (int i = 1; i < argc; ++i)
	{
		std::istringstream iss(argv[i]);
		std::string token;
		while (iss >> token)
			_vec.push_back(parseNumber(token));
	}
	if (_vec.empty())
		throw std::runtime_error("no input");
}

void PmergeMe::loadDeque(int argc, char** argv)
{
	_deq.clear();
	for (int i = 1; i < argc; ++i)
	{
		std::istringstream iss(argv[i]);
		std::string token;
		while (iss >> token)
			_deq.push_back(parseNumber(token));
	}
	if (_deq.empty())
		throw std::runtime_error("no input");
}

void PmergeMe::sortVector()
{
	sortByIndex<std::vector<size_t> >(_vec);
}

void PmergeMe::sortDeque()
{
	sortByIndex<std::deque<size_t> >(_deq);
}
