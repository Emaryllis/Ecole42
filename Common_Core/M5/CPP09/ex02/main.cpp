#include <exception>
#include <iostream>
#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}

	try {
		PmergeMe sorter;
		sorter.run(argc, argv);
	} catch (const std::exception &) {
		// Prints "Error" like the subject. Name the exception and print e.what() to see the reason.
		std::cerr << "Error" << std::endl;
		return 1;
	}
	return 0;
}
