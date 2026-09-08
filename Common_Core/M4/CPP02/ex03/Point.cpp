#include "Point.hpp"
#include <iostream>

Point::Point() : x(Fixed()), y(Fixed()) {
	std::cout << "Point default constructor called." << std::endl;
}

Point::Point(const float x, const float y) : x(Fixed(x)), y(Fixed(y)) {
	std::cout << "Point Float constructor called." << std::endl;
}

Point::~Point() {
	std::cout << "Point destructor Called" << std::endl;
}

Point::Point(const Point &other) : x(other.x), y(other.y) {
	std::cout << "Point copy constructor called." << std::endl;
}

Point &Point::operator=(const Point &obj) {
	if (this != &obj) {
		const_cast<Fixed &>(x) = obj.x;
		const_cast<Fixed &>(y) = obj.x;
	}
	return *this;
}

const Fixed &Point::getX() const {
	return x;
}

const Fixed &Point::getY() const {
	return y;
}
