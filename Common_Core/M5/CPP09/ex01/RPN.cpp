#include "RPN.hpp"
#include <cctype>
#include <limits>
#include <sstream>
#include <stdexcept>

RPN::RPN() {}

RPN::RPN(const RPN &other): _operands(other._operands) {}

RPN &RPN::operator=(const RPN &other) {
	if (this != &other) {
		_operands = other._operands;
	}
	return *this;
}

RPN::~RPN() {}

// Every operation is checked before it runs, because signed overflow is undefined behaviour in C++.
static long add(const long lhs, const long rhs) {
	if ((rhs > 0 && lhs > std::numeric_limits<long>::max() - rhs) ||
	    (rhs < 0 && lhs < std::numeric_limits<long>::min() - rhs)) {
		throw std::overflow_error("overflow");
	}
	return lhs + rhs;
}

static long subtract(const long lhs, const long rhs) {
	if ((rhs < 0 && lhs > std::numeric_limits<long>::max() + rhs) ||
	    (rhs > 0 && lhs < std::numeric_limits<long>::min() + rhs)) {
		throw std::overflow_error("overflow");
	}
	return lhs - rhs;
}

static long multiply(const long lhs, const long rhs) {
	if (lhs == 0 || rhs == 0) {
		return 0;
	}
	const long max = std::numeric_limits<long>::max();
	const long min = std::numeric_limits<long>::min();
	if ((lhs > 0 && rhs > 0 && lhs > max / rhs) || (lhs < 0 && rhs < 0 && lhs < max / rhs) ||
	    (lhs > 0 && rhs < 0 && rhs < min / lhs) || (lhs < 0 && rhs > 0 && lhs < min / rhs)) {
		throw std::overflow_error("overflow");
	}
	return lhs * rhs;
}

// Integer division, rounded towards zero like C++ does: "7 2 /" gives 3.
static long divide(const long lhs, const long rhs) {
	if (rhs == 0) {
		throw std::domain_error("division by zero");
	}
	if (lhs == std::numeric_limits<long>::min() && rhs == -1) {
		throw std::overflow_error("overflow");
	}
	return lhs / rhs;
}

static bool isOperator(const char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

// Tokens are separated by whitespace and are exactly one character long:
// a digit from 0 to 9, or one of the operators + - * /
long RPN::evaluate(const std::string &expression) {
	_operands = std::stack<long, std::list<long> >();

	std::istringstream stream(expression);
	std::string token;
	while (stream >> token) {
		if (token.size() != 1) {
			throw std::invalid_argument("invalid token: " + token);
		}
		const char c = token[0];
		if (std::isdigit(static_cast<unsigned char>(c))) {
			_operands.push(c - '0');
		} else if (isOperator(c)) {
			applyOperator(c);
		} else {
			throw std::invalid_argument("invalid token: " + token);
		}
	}
	if (_operands.empty()) {
		throw std::invalid_argument("empty expression");
	}
	if (_operands.size() != 1) {
		throw std::invalid_argument("too many operands");
	}
	return _operands.top();
}

// The right operand is on top of the stack: "8 2 -" pops 2 first, then 8, and computes 8 - 2.
void RPN::applyOperator(const char op) {
	if (_operands.size() < 2) {
		throw std::invalid_argument("not enough operands");
	}
	const long rhs = _operands.top();
	_operands.pop();
	const long lhs = _operands.top();
	_operands.pop();

	switch (op) {
		case '+':
			_operands.push(add(lhs, rhs));
			break;
		case '-':
			_operands.push(subtract(lhs, rhs));
			break;
		case '*':
			_operands.push(multiply(lhs, rhs));
			break;
		default:
			_operands.push(divide(lhs, rhs));
			break;
	}
}