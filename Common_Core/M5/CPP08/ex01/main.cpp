#include <iostream>
#include <vector>
#include "Span.hpp"

int main() {
	Span sp(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
	std::cout << "Longest span: " << sp.longestSpan() << std::endl;

	try {
		sp.addNumber(20);
	} catch (std::exception &e) {
		std::cerr << "Expected exception: " << e.what() << std::endl;
	}

	Span big_sp(100000);
	std::vector<int> vec;
	for (int i = 0; i < 10000; ++i) {
		vec.push_back(i);
	}

	big_sp.addNumbers(vec.begin(), vec.end());
	std::cout << "Big Span - Shortest: " << big_sp.shortestSpan() << std::endl;
	std::cout << "Big Span - Longest: " << big_sp.longestSpan() << std::endl;

	return 0;
}