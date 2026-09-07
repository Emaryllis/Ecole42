#include "Point.hpp"
#include <iostream>

int main() {
	const Point a;
	const Point b(10, 30);
	const Point c(20, 0);
	const Point point(10.5f, 15.5f);
	if (bsp(a, b, c, point))
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	return 0;
}
