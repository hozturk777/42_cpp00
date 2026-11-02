#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
private:
	std::map<std::string, double>	_db;

	bool	isValidDate(const std::string& date) const;
	bool	parseValue(const std::string& str, double& value) const;
	double	getRate(const std::string& date) const;
	void	processLine(const std::string& line) const;

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void	loadDatabase(const std::string& path);
	void	processInput(const std::string& path) const;
};

#endif
