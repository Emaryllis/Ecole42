#include "Fixed.hpp"
#include <iostream>
#include <cmath>

const int Fixed::fracBits = 8;

Fixed::Fixed() : fixedPoint(0) {
	std::cout << "default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &obj): fixedPoint(obj.getRawBits()) {
	std::cout << "copy constructor called" << std::endl;
}

Fixed::Fixed(int num) : fixedPoint(num << fracBits) {
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(float num) : fixedPoint(
	static_cast<int>(roundf(num * (1 << fracBits)))) {
	std::cout << "Float constructor called" << std::endl;
}

Fixed::~Fixed() {
	std::cout << "destructor called" << std::endl;
}

Fixed &Fixed::operator=(const Fixed &obj) {
	std::cout << "copy assignment operator called" << std::endl;
	if (this != &obj) {
		this->fixedPoint = obj.fixedPoint;
	}
	return *this;
}

int Fixed::getRawBits() const {
	std::cout << "getRawBits member function called" << std::endl;
	return fixedPoint;
}

int Fixed::toInt() const {
	return fixedPoint >> fracBits;
}

float Fixed::toFloat() const {
	return static_cast<float>(fixedPoint) / static_cast<float>(1 << fracBits);
}

bool Fixed::operator>(const Fixed &other) const {
	return fixedPoint > other.fixedPoint;
}

bool Fixed::operator<(const Fixed &other) const {
	return fixedPoint < other.fixedPoint;
}

bool Fixed::operator>=(const Fixed &other) const {
	return fixedPoint >= other.fixedPoint;
}

bool Fixed::operator<=(const Fixed &other) const {
	return fixedPoint <= other.fixedPoint;
}

bool Fixed::operator==(const Fixed &other) const {
	return fixedPoint == other.fixedPoint;
}

bool Fixed::operator!=(const Fixed &other) const {
	return fixedPoint != other.fixedPoint;
}

Fixed Fixed::operator*(const Fixed &other) const {
	Fixed res(toFloat() * other.toFloat());
	return res;
}

Fixed Fixed::operator/(const Fixed &other) const {
	Fixed res(toFloat() / other.toFloat());
	return res;
}

Fixed Fixed::operator+(const Fixed &other) const {
	Fixed res(toFloat() + other.toFloat());
	return res;
}

Fixed Fixed::operator-(const Fixed &other) const {
	Fixed res(toFloat() - other.toFloat());
	return res;
}

Fixed Fixed::operator++() {
	++fixedPoint;
	return *this;
}

Fixed Fixed::operator++(int) {
	Fixed original(*this);
	++fixedPoint;
	return original;
}

Fixed Fixed::operator--() {
	--fixedPoint;
	return *this;
}

Fixed Fixed::operator--(int) {
	Fixed original(*this);
	--fixedPoint;
	return original;
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
	return a > b ? a : b;
}

Fixed &Fixed::min(Fixed &a, Fixed &b) {
	return a < b ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
	return a > b ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
	return a < b ? a : b;
}

std::ostream &operator <<(std::ostream &out, const Fixed &obj) {
	out << obj.toFloat();
	return out;
}
