#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	~BitcoinExchange();

	void loadDatabase(const std::string &path);
	void processInput(const std::string &path) const;

private:
	// std::map keeps the dates sorted and unique, and upper_bound() finds the closest earlier date in O(log n).
	// Keys are "YYYY-MM-DD" strings: with a fixed width format, alphabetical order is chronological order.
	std::map<std::string, double> _rates;

	void processLine(const std::string &line) const;
};

#endif
