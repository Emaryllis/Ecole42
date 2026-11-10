#include <exception>
#include <iostream>
#include "RPN.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}

	try {
		RPN calculator;
		const long result = calculator.evaluate(argv[1]);
		std::cout << result << std::endl;
	} catch (const std::exception &) {
		// Prints "Error" like the subject. Name the exception and print e.what() to see the reason.
		std::cerr << "Error" << std::endl;
		return 1;
	}
	return 0;
}
