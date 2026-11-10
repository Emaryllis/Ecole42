#include "BitcoinExchange.hpp"
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

static const std::string DATABASE_HEADER = "date,exchange_rate";
static const std::string INPUT_HEADER = "date | value";
static const std::string INPUT_SEPARATOR = " | ";
static const std::string MAX_VALUE = "1000";

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other): _rates(other._rates) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other) {
		_rates = other._rates;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

// Files saved with Windows line endings (CRLF) leave a '\r' at the end of every line read by std::getline.
static std::string stripCarriageReturn(const std::string &line) {
	if (!line.empty() && line[line.size() - 1] == '\r') {
		return line.substr(0, line.size() - 1);
	}
	return line;
}

// Some editors (Excel, Notepad) start a UTF-8 file with an invisible byte order mark, which would hide the header.
static std::string stripByteOrderMark(const std::string &line) {
	if (line.compare(0, 3, "\xEF\xBB\xBF") == 0) {
		return line.substr(3);
	}
	return line;
}

static bool isDigit(const char c) {
	return std::isdigit(static_cast<unsigned char>(c)) != 0;
}

// Digits, optionally followed by a '.' and more digits: "42", "0.5", "1000.000".
// Rejects everything else std::strtod would accept: "", ".5", "5.", "1e3", "0x10", "inf", "nan", spaces...
static bool isUnsignedDecimal(const std::string &str) {
	std::size_t i = 0;
	while (i < str.size() && isDigit(str[i])) {
		++i;
	}
	if (i == 0) {
		return false;
	}
	if (i == str.size()) {
		return true;
	}
	if (str[i] != '.') {
		return false;
	}
	const std::size_t fractionStart = ++i;
	while (i < str.size() && isDigit(str[i])) {
		++i;
	}
	return i == str.size() && i > fractionStart;
}

// An unsigned decimal with an optional '+' or '-' sign in front.
static bool isSignedDecimal(const std::string &str) {
	if (!str.empty() && (str[0] == '+' || str[0] == '-')) {
		return isUnsignedDecimal(str.substr(1));
	}
	return isUnsignedDecimal(str);
}

// Compares the text with MAX_VALUE rather than the parsed double, which cannot hold every decimal:
// std::strtod turns "1000.0000000000000001" into exactly 1000. Only called on values that passed
// isSignedDecimal and do not start with '-'.
static bool isAboveMaxValue(const std::string &value) {
	const std::string number = (value[0] == '+') ? value.substr(1) : value;
	const std::string::size_type dot = number.find('.');
	std::string integerPart = number.substr(0, dot);
	const std::string fractionPart = (dot == std::string::npos) ? "" : number.substr(dot + 1);

	const std::string::size_type firstNonZero = integerPart.find_first_not_of('0');
	integerPart = (firstNonZero == std::string::npos) ? "0" : integerPart.substr(firstNonZero);
	if (integerPart.size() != MAX_VALUE.size()) {
		return integerPart.size() > MAX_VALUE.size();
	}
	if (integerPart != MAX_VALUE) {
		return integerPart > MAX_VALUE;
	}
	return fractionPart.find_first_not_of('0') != std::string::npos;
}

// Gregorian calendar: every 4th year is a leap year, except centuries, except every 400th year.
// 2012 and 2000 are leap years, 2013, 1900 and 2100 are not.
static bool isLeapYear(const int year) {
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

static int daysInMonth(const int year, const int month) {
	static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (month == 2 && isLeapYear(year)) {
		return 29;
	}
	return days[month - 1];
}

// Checks the shape only: "YYYY-MM-DD" with a 4 digit year and 2 digit month and day.
static bool hasDateFormat(const std::string &date) {
	if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
		return false;
	}
	for (std::size_t i = 0; i < date.size(); ++i) {
		if (i != 4 && i != 7 && !isDigit(date[i])) {
			return false;
		}
	}
	return true;
}

// Only called on the digits of a date that passed hasDateFormat.
static int toNumber(const std::string &str, const std::size_t pos, const std::size_t length) {
	int number = 0;
	for (std::size_t i = pos; i < pos + length; ++i) {
		number = number * 10 + (str[i] - '0');
	}
	return number;
}

// Checks the calendar: month 1-12, day 1 up to the last day of that month, Feb 29 only in leap years.
static bool isValidDate(const std::string &date) {
	if (!hasDateFormat(date)) {
		return false;
	}
	const int year = toNumber(date, 0, 4);
	const int month = toNumber(date, 5, 2);
	const int day = toNumber(date, 8, 2);
	return month >= 1 && month <= 12 && day >= 1 && day <= daysInMonth(year, month);
}

// Prints up to 10 significant digits: 0.9 instead of 0.899999..., 66063560 instead of 6.60636e+07.
static std::string formatNumber(const double number) {
	std::ostringstream stream;
	stream.precision(10);
	stream << number;
	return stream.str();
}

static std::runtime_error databaseError(const std::string &path, const std::size_t lineNumber,
                                        const std::string &reason, const std::string &line) {
	std::ostringstream message;
	message << path << " line " << lineNumber << ": " << reason << " => " << line;
	return std::runtime_error(message.str());
}

void BitcoinExchange::loadDatabase(const std::string &path) {
	std::ifstream file(path.c_str());
	if (!file.is_open()) {
		throw std::runtime_error("could not open database " + path + ".");
	}

	// Filled separately and swapped in at the end, so a failed load leaves the current rates untouched.
	std::map<std::string, double> rates;
	std::string line;
	std::size_t lineNumber = 0;
	while (std::getline(file, line)) {
		++lineNumber;
		line = stripCarriageReturn(line);
		if (lineNumber == 1) {
			line = stripByteOrderMark(line);
			if (line == DATABASE_HEADER) {
				continue;
			}
		}
		const std::string::size_type comma = line.find(',');
		if (comma == std::string::npos) {
			throw databaseError(path, lineNumber, "expected \"date,exchange_rate\"", line);
		}
		const std::string date = line.substr(0, comma);
		const std::string rate = line.substr(comma + 1);
		if (!isValidDate(date)) {
			throw databaseError(path, lineNumber, "invalid date", line);
		}
		if (!isUnsignedDecimal(rate)) {
			throw databaseError(path, lineNumber, "invalid exchange rate", line);
		}
		const double value = std::strtod(rate.c_str(), NULL);
		if (value > std::numeric_limits<double>::max()) {
			throw databaseError(path, lineNumber, "exchange rate too large", line);
		}
		if (!rates.insert(std::make_pair(date, value)).second) {
			throw databaseError(path, lineNumber, "duplicate date", line);
		}
	}
	if (file.bad()) {
		throw std::runtime_error("could not read database " + path + ".");
	}
	if (rates.empty()) {
		throw std::runtime_error("database " + path + " has no exchange rates.");
	}
	_rates.swap(rates);
}

void BitcoinExchange::processInput(const std::string &path) const {
	std::ifstream file(path.c_str());
	if (!file.is_open()) {
		throw std::runtime_error("could not open file.");
	}

	std::string line;
	bool isFirstLine = true;
	while (std::getline(file, line)) {
		line = stripCarriageReturn(line);
		if (isFirstLine) {
			isFirstLine = false;
			line = stripByteOrderMark(line);
			if (line == INPUT_HEADER) {
				continue;
			}
		}
		processLine(line);
	}
	if (file.bad()) {
		throw std::runtime_error("could not read file.");
	}
	if (isFirstLine) {
		throw std::runtime_error("file is empty.");
	}
}

// Expected format: "date | value". Checks are done in this order:
// 1. the shape of the line, the date and the value  -> "bad input"
// 2. the date exists in the calendar                 -> "invalid date"
// 3. the value is not negative                       -> "not a positive number"
// 4. the value is at most 1000                       -> "too large a number"
// 5. the database has a rate on or before that date  -> "no exchange rate available"
void BitcoinExchange::processLine(const std::string &line) const {
	const std::string::size_type separator = line.find(INPUT_SEPARATOR);
	if (separator == std::string::npos) {
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}
	const std::string date = line.substr(0, separator);
	const std::string value = line.substr(separator + INPUT_SEPARATOR.size());
	if (!hasDateFormat(date) || !isSignedDecimal(value)) {
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}
	if (!isValidDate(date)) {
		std::cout << "Error: invalid date => " << date << std::endl;
		return;
	}
	if (value[0] == '-') {
		std::cout << "Error: not a positive number." << std::endl;
		return;
	}
	if (isAboveMaxValue(value)) {
		std::cout << "Error: too large a number." << std::endl;
		return;
	}
	const double amount = std::strtod(value.c_str(), NULL);

	// upper_bound gives the first date after the input date, so the entry just before it is
	// the same date, or the closest earlier one when the exact date is not in the database.
	std::map<std::string, double>::const_iterator rate = _rates.upper_bound(date);
	if (rate == _rates.begin()) {
		std::cout << "Error: no exchange rate available before " << _rates.begin()->first << " => " << date
				<< std::endl;
		return;
	}
	--rate;
	std::cout << date << " => " << value << " = " << formatNumber(amount * rate->second) << std::endl;
}