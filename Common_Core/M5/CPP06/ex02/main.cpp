#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Base.hpp"
#include "Identify.hpp"

int main() {
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	for (int i = 0; i < 5; ++i) {
		Base *ptr = generate();

		std::cout << "Identified ptr: ";
		identify(ptr);

		std::cout << "Identified address ptr: ";
		identify(*ptr);

		delete ptr;
	}

	return 0;
}