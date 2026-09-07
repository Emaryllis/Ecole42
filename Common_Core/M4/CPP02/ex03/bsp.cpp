#include "Point.hpp"

float cross(const Point &p1, const Point &p2, const Point &p) {
	const float x1 = p2.getX().toFloat() - p1.getX().toFloat();
	const float y1 = p2.getY().toFloat() - p1.getY().toFloat();
	const float x2 = p.getX().toFloat() - p1.getX().toFloat();
	const float y2 = p.getY().toFloat() - p1.getY().toFloat();
	return x1 * y2 - y1 * x2;
}

// Half-Space / Edge-Cross Product Method
bool bsp(const Point &a, const Point &b, const Point &c, const Point &point) {
	const float cross1 = cross(a, b, point);
	const float cross2 = cross(b, c, point);
	const float cross3 = cross(c, a, point);

	const bool has_neg = cross1 < 0 || cross2 < 0 || cross3 < 0;
	const bool has_pos = cross1 > 0 || cross2 > 0 || cross3 > 0;

	// If point is not outside the triangle and not on the edges = if point is inside the triangle
	return !(has_neg && has_pos) && cross1 != 0 && cross2 != 0 && cross3 != 0;
}
