#include <iostream>
#include <string>
#include "iter.hpp"

template <typename T>
void printElement(T const &x) {
	std::cout << x << " ";
}

void increment(int &x) {
	x += 1;
}

int main(void) {
	int intArray[] = {1, 2, 3, 4, 5};
	const std::size_t intLen = sizeof(intArray) / sizeof(intArray[0]);

	std::cout << "Original int array: ";
	::iter(intArray, intLen, printElement<int>);
	std::cout << std::endl;

	::iter(intArray, intLen, increment);

	std::cout << "Incremented int array: ";
	::iter(intArray, intLen, printElement<int>);
	std::cout << std::endl;

	std::string strArray[] = {"hello", "world", "cpp"};
	const std::size_t strLen = sizeof(strArray) / sizeof(strArray[0]);

	std::cout << "String array: ";
	::iter(strArray, strLen, printElement<std::string>);
	std::cout << std::endl;

	return 0;
}