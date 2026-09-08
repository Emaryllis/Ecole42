#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Array.hpp"

#define MAX_VAL 750

/**
 * Modified version of the given main.cpp to test the Array class template.
 * @return
 */
int main(int, char**) {
	Array<int> numbers(MAX_VAL);
	int* mirror = new int[MAX_VAL];
	std::srand(std::time(NULL));
	for (int i = 0; i < MAX_VAL; i++) {
		const int value = std::rand();
		numbers[i] = value;
		mirror[i] = value;
	}
	const Array<int> tmp = numbers;

	for (int i = 0; i < MAX_VAL; i++) {
		if (mirror[i] != numbers[i]) {
			std::cerr << "didn't save the same value!!" << std::endl;
			return 1;
		}
	}
	try {
		numbers[-2] = 0;
	} catch(const std::exception &e) {
		std::cerr << e.what() << '\n';
	}
	try {
		numbers[MAX_VAL] = 0;
	} catch(const std::exception &e) {
		std::cerr << e.what() << '\n';
	}

	for (int i = 0; i < MAX_VAL; i++) {
		numbers[i] = std::rand();
	}
	delete[] mirror;
	return 0;
}