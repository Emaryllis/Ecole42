#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point {
public:
	Point();
	Point(const float x, const float y);
	~Point();
	Point(const Point &obj);
	Point &operator=(const Point &obj);
	const Fixed &getX() const;
	const Fixed &getY() const;

private:
	const Fixed x;
	const Fixed y;
};

bool bsp(const Point &a, const Point &b, const Point &c, const Point &point);

#endif
