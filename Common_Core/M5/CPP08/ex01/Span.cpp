#include <algorithm>
#include <climits>
#include <iostream>
#include "Span.hpp"

Span::Span() : _maxSize(0) {
	std::cout << "Span default constructor called" << std::endl;
}

Span::Span(const unsigned int n) : _maxSize(n) {
	std::cout << "Span constructor called with max size " << _maxSize << std::endl;
}

Span::Span(const Span &other) : _maxSize(other._maxSize), _numbers(other._numbers) {
	std::cout << "Span copy constructor called" << std::endl;
}

Span::~Span() {
	std::cout << "Span destructor called" << std::endl;
}

Span::SpanException::SpanException(const char *msg) throw() : _msg(msg) {
	std::cout << "SpanException parameterized constructor called" << std::endl;
}

const char *Span::SpanException::what() const throw() {
	return _msg;
}

Span &Span::operator=(const Span &rhs) {
	std::cout << "Span copy assignment operator called" << std::endl;
	if (this != &rhs) {
		this->_maxSize = rhs._maxSize;
		this->_numbers = rhs._numbers;
	}
	return *this;
}

void Span::addNumber(const int num) {
	if (_numbers.size() >= static_cast<size_t>(_maxSize)) {
		throw SpanException("Span is full! Cannot add more numbers.");
	}
	_numbers.push_back(num);
}

int Span::shortestSpan() const {
	if (_numbers.size() < 2) {
		throw SpanException("Not enough numbers to find a span!");
	}

	std::vector<int> sorted_numbers = _numbers;
	std::sort(sorted_numbers.begin(), sorted_numbers.end());

	int min_span = INT_MAX;
	for (size_t i = 1; i < sorted_numbers.size(); ++i) {
		const int span = sorted_numbers[i] - sorted_numbers[i - 1];
		if (span < min_span) {
			min_span = span;
		}
	}
	return min_span;
}

int Span::longestSpan() const {
	if (_numbers.size() < 2) {
		throw SpanException("Not enough numbers to find a span!");
	}

	const std::vector<int>::const_iterator min_it = std::min_element(_numbers.begin(), _numbers.end());
	const std::vector<int>::const_iterator max_it = std::max_element(_numbers.begin(), _numbers.end());

	const long long diff = static_cast<long long>(*max_it) - static_cast<long long>(*min_it);
	return static_cast<int>(diff);
}