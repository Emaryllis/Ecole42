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

void Fixed::setRawBits(int raw) {
	this->fixedPoint = raw;
}

int Fixed::toInt() const {
	return fixedPoint >> fracBits;
}

float Fixed::toFloat() const {
	return static_cast<float>(fixedPoint) / static_cast<float>(1 << fracBits);
}

std::ostream &operator <<(std::ostream &out, const Fixed &obj) {
	out << obj.toFloat();
	return out;
}
