#include <climits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <vector>
#include "Span.hpp"

static void testSubject() {
	std::cout << "\n===== Subject test =====" << std::endl;
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	try {
		sp.addNumber(20);
	} catch (const std::exception &e) {
		std::cout << "Expected exception: " << e.what() << std::endl;
	}
}

static void testNotEnoughNumbers() {
	std::cout << "\n===== Not enough numbers =====" << std::endl;
	Span empty(3);
	try {
		empty.shortestSpan();
	} catch (const std::exception &e) {
		std::cout << "Expected exception (0 numbers): " << e.what() << std::endl;
	}
	empty.addNumber(42);
	try {
		empty.longestSpan();
	} catch (const std::exception &e) {
		std::cout << "Expected exception (1 number): " << e.what() << std::endl;
	}

	Span zero(0);
	try {
		zero.addNumber(1);
	} catch (const std::exception &e) {
		std::cout << "Expected exception (Span(0)): " << e.what() << std::endl;
	}
}

static void testExtremes() {
	std::cout << "\n===== INT_MIN / INT_MAX =====" << std::endl;
	Span sp(3);
	sp.addNumber(INT_MIN);
	sp.addNumber(INT_MAX);
	sp.addNumber(0);
	std::cout << "Shortest span: " << sp.shortestSpan() << " (expected " << INT_MAX << ")" << std::endl;
	std::cout << "Longest span: " << sp.longestSpan() << " (expected 4294967295)" << std::endl;

	Span dup(2);
	dup.addNumber(7);
	dup.addNumber(7);
	std::cout << "Shortest span with duplicates: " << dup.shortestSpan() << std::endl;
}

static void testAddRange() {
	std::cout << "\n===== addNumbers with iterator range =====" << std::endl;
	std::list<int> lst;
	lst.push_back(100);
	lst.push_back(-50);
	lst.push_back(30);

	Span sp(5);
	sp.addNumbers(lst.begin(), lst.end());
	std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
	std::cout << "Longest span: " << sp.longestSpan() << std::endl;

	std::vector<int> tooMany(3, 1);
	try {
		sp.addNumbers(tooMany.begin(), tooMany.end());
	} catch (const std::exception &e) {
		std::cout << "Expected exception: " << e.what() << std::endl;
	}
	std::cout << "Span unchanged after failed range insert, longest span: " << sp.longestSpan() << std::endl;
}

static void testBig() {
	std::cout << "\n===== 10,000 random numbers =====" << std::endl;
	const int count = 10000;
	std::vector<int> vec;
	std::srand(std::time(NULL));
	for (int i = 0; i < count; ++i) {
		vec.push_back(std::rand());
	}

	Span big(count);
	big.addNumbers(vec.begin(), vec.end());
	std::cout << "Shortest span: " << big.shortestSpan() << std::endl;
	std::cout << "Longest span: " << big.longestSpan() << std::endl;
}

static void testCopy() {
	std::cout << "\n===== Copy / assignment =====" << std::endl;
	Span original(3);
	original.addNumber(1);
	original.addNumber(10);

	Span copy(original);
	copy.addNumber(100);
	std::cout << "Original longest: " << original.longestSpan() << ", copy longest: " << copy.longestSpan()
			<< std::endl;

	Span assigned(1);
	assigned = copy;
	std::cout << "Assigned longest: " << assigned.longestSpan() << std::endl;
}

int main() {
	testSubject();
	testNotEnoughNumbers();
	testExtremes();
	testAddRange();
	testBig();
	testCopy();
	return 0;
}