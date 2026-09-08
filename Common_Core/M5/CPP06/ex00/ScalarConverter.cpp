#include <cstdlib>
#include <cmath>
#include <limits>
#include <cctype>
#include <iostream>
#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {
	std::cout << "ScalarConverter default constructor called" << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter &other) {
	(void) other;
	std::cout << "ScalarConverter copy constructor called" << std::endl;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other) {
	(void) other;
	std::cout << "ScalarConverter copy assignment operator called" << std::endl;
	return *this;
}

ScalarConverter::~ScalarConverter() {
	std::cout << "ScalarConverter destructor called" << std::endl;
}

static bool isPseudoLiteral(const std::string &str) {
	return str == "-inff" || str == "+inff" || str == "nanf" ||
	       str == "-inf" || str == "+inf" || str == "nan";
}

static void printChar(double val, bool isPseudo) {
	std::cout << "char: ";
	if (isPseudo || val < std::numeric_limits<char>::min() || val > std::numeric_limits<char>::max() ||
	    std::isnan(val)) {
		std::cout << "impossible" << std::endl;
	} else if (!std::isprint(static_cast<char>(val))) {
		std::cout << "Non displayable" << std::endl;
	} else {
		std::cout << "'" << static_cast<char>(val) << "'" << std::endl;
	}
}

static void printInt(double val, bool isPseudo) {
	std::cout << "int: ";
	if (isPseudo || val < std::numeric_limits<int>::min() || val > std::numeric_limits<int>::max() || std::isnan(val)) {
		std::cout << "impossible" << std::endl;
	} else {
		std::cout << static_cast<int>(val) << std::endl;
	}
}

static void printFloat(double val, const std::string &str) {
	std::cout << "float: ";
	if (str == "-inf" || str == "-inff") {
		std::cout << "-inff" << std::endl;
	} else if (str == "+inf" || str == "+inff") {
		std::cout << "+inff" << std::endl;
	} else if (str == "nan" || str == "nanf") {
		std::cout << "nanf" << std::endl;
	} else {
		const float f = static_cast<float>(val);
		std::cout << f;
		if (f == static_cast<int>(f)) {
			std::cout << ".0";
		}
		std::cout << "f" << std::endl;
	}
}

static void printDouble(double val, const std::string &str) {
	std::cout << "double: ";
	if (str == "-inf" || str == "-inff") {
		std::cout << "-inf" << std::endl;
	} else if (str == "+inf" || str == "+inff") {
		std::cout << "+inf" << std::endl;
	} else if (str == "nan" || str == "nanf") {
		std::cout << "nan" << std::endl;
	} else {
		std::cout << val;
		if (val == static_cast<int>(val)) {
			std::cout << ".0";
		}
		std::cout << std::endl;
	}
}

void ScalarConverter::convert(const std::string &literal) {
	double val = 0.0;
	const bool pseudo = isPseudoLiteral(literal);

	if (literal.length() == 1 && !std::isdigit(literal[0])) {
		val = static_cast<double>(literal[0]);
	} else if (pseudo) {
		val = 0.0;
	} else {
		char *endPtr;
		std::string strToParse = literal;
		if (strToParse.length() > 1 && strToParse[strToParse.length() - 1] == 'f') {
			strToParse = strToParse.substr(0, strToParse.length() - 1);
		}
		val = std::strtod(strToParse.c_str(), &endPtr);
		if (*endPtr != '\0') {
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
			return;
		}
	}

	printChar(val, pseudo);
	printInt(val, pseudo);
	printFloat(val, literal);
	printDouble(val, literal);
}