#include <algorithm>
#include <iostream>
#include "Span.hpp"

Span::Span(): _maxSize(0) {
	std::cout << "Span default constructor called" << std::endl;
}

Span::Span(const unsigned int n): _maxSize(n) {
	std::cout << "Span constructor called with max size " << _maxSize << std::endl;
}

Span::Span(const Span &other): _maxSize(other._maxSize), _numbers(other._numbers) {
	std::cout << "Span copy constructor called" << std::endl;
}

Span::~Span() {
	std::cout << "Span destructor called" << std::endl;
}

Span::SpanException::SpanException(const char *msg) throw(): _msg(msg) {}

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

long Span::shortestSpan() const {
	if (_numbers.size() < 2) {
		throw SpanException("Not enough numbers to find a span!");
	}

	std::vector<int> sorted_numbers = _numbers;
	std::sort(sorted_numbers.begin(), sorted_numbers.end());

	long min_span = static_cast<long>(sorted_numbers[1]) - static_cast<long>(sorted_numbers[0]);
	for (size_t i = 2; i < sorted_numbers.size(); ++i) {
		const long span = static_cast<long>(sorted_numbers[i]) - static_cast<long>(sorted_numbers[i - 1]);
		if (span < min_span) {
			min_span = span;
		}
	}
	return min_span;
}

long Span::longestSpan() const {
	if (_numbers.size() < 2) {
		throw SpanException("Not enough numbers to find a span!");
	}

	const std::vector<int>::const_iterator min_it = std::min_element(_numbers.begin(), _numbers.end());
	const std::vector<int>::const_iterator max_it = std::max_element(_numbers.begin(), _numbers.end());

	return static_cast<long>(*max_it) - static_cast<long>(*min_it);
}