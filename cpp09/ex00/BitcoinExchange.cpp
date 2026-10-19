#include "BitcoinExchange.hpp"
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _db(other._db) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_db = other._db;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

// Bastaki ve sondaki bosluk / tab / '\r' karakterlerini atar (Windows satir sonlari icin)
static std::string trim(const std::string& s)
{
	std::string::size_type start = s.find_first_not_of(" \t\r");
	if (start == std::string::npos)
		return "";
	std::string::size_type end = s.find_last_not_of(" \t\r");
	return s.substr(start, end - start + 1);
}

// YYYY-MM-DD formati + ay araligi + ayin gun sayisi (artik yil dahil)
bool BitcoinExchange::isValidDate(const std::string& date) const
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (size_t i = 0; i < date.size(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return false;
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	if (month < 1 || month > 12 || day < 1)
		return false;

	int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	bool leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	if (month == 2 && leap)
		return day <= 29;
	return day <= days[month - 1];
}

// Sadece [-]rakamlar[.rakamlar] formatini kabul eder; aralik kontrolu cagiran tarafta
// ('-' kabul edilir ki negatif deger "not a positive number" hatasini alabilsin)
bool BitcoinExchange::parseValue(const std::string& str, double& value) const
{
	size_t i = 0;
	if (i < str.size() && str[i] == '-')
		++i;
	size_t digits = 0;
	while (i < str.size() && std::isdigit(static_cast<unsigned char>(str[i])))
	{
		++i;
		++digits;
	}
	if (i < str.size() && str[i] == '.')
	{
		++i;
		size_t frac = 0;
		while (i < str.size() && std::isdigit(static_cast<unsigned char>(str[i])))
		{
			++i;
			++frac;
		}
		if (frac == 0)
			return false;
	}
	if (digits == 0 || i != str.size())
		return false;
	value = std::strtod(str.c_str(), NULL);
	return true;
}

// upper_bound: tarihten kesin buyuk ilk eleman. Bir geri = esit ya da en yakin alt tarih.
double BitcoinExchange::getRate(const std::string& date) const
{
	std::map<std::string, double>::const_iterator it = _db.upper_bound(date);
	if (it == _db.begin())
		throw std::runtime_error("no data before => " + date);
	--it;
	return it->second;
}

void BitcoinExchange::loadDatabase(const std::string& path)
{
	std::ifstream file(path.c_str());
	if (!file.is_open())
		throw std::runtime_error("could not open database.");

	std::string line;
	std::getline(file, line); // "date,exchange_rate" basligi
	while (std::getline(file, line))
	{
		line = trim(line);
		size_t comma = line.find(',');
		if (comma == std::string::npos)
			continue;
		std::string date = line.substr(0, comma);
		double rate;
		if (!isValidDate(date) || !parseValue(line.substr(comma + 1), rate))
			continue;
		_db[date] = rate;
	}
	if (_db.empty())
		throw std::runtime_error("database is empty.");
}

void BitcoinExchange::processLine(const std::string& rawLine) const
{
	std::string line = trim(rawLine);
	std::string::size_type sep = line.find(" | ");
	if (sep == std::string::npos)
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}

	std::string date = line.substr(0, sep);
	std::string valueStr = trim(line.substr(sep + 3));
	double value;
	if (!isValidDate(date) || !parseValue(valueStr, value))
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}
	if (value < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return;
	}
	if (value > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return;
	}

	try
	{
		double rate = getRate(date);
		std::cout << date << " => " << valueStr << " = " << value * rate << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

void BitcoinExchange::processInput(const std::string& path) const
{
	std::ifstream file(path.c_str());
	if (!file.is_open())
		throw std::runtime_error("could not open file.");

	std::string line;
	bool first = true;
	while (std::getline(file, line))
	{
		// Ilk satir baslik ise atla; degilse normal satir gibi isle
		if (first)
		{
			first = false;
			if (trim(line) == "date | value")
				continue;
		}
		processLine(line);
	}
}
