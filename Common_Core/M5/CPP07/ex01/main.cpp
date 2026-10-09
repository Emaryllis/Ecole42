#include <iostream>
#include <string>
#include "iter.hpp"

template<typename T>
void printElement(T const &x) {
	std::cout << x << ' ';
}

template<typename T>
void increment(T &x) {
	x += 1;
}

template<typename T>
void appendBang(T &x) {
	x += '!';
}

int main(void) {
	int intArray[] = {1, 2, 3, 4, 5};
	const std::size_t intLen = sizeof(intArray) / sizeof(intArray[0]);

	const int constIntArray[] = {10, 20, 30};
	const std::size_t constIntLen = sizeof(constIntArray) / sizeof(constIntArray[0]);

	std::string strArray[] = {"hello", "world", "cpp"};
	const std::size_t strLen = sizeof(strArray) / sizeof(strArray[0]);

	const std::string constStrArray[] = {"foo", "bar", "baz"};
	const std::size_t constStrLen = sizeof(constStrArray) / sizeof(constStrArray[0]);

	std::cout << "Original int array: ";
	::iter(intArray, intLen, ::printElement<int>);
	std::cout << std::endl;

	::iter(intArray, intLen, ::increment<int>);
	std::cout << "Incremented int array: ";
	::iter(intArray, intLen, ::printElement<int>);
	std::cout << std::endl;

	std::cout << "Const int array: ";
	::iter(constIntArray, constIntLen, ::printElement<int>);
	std::cout << std::endl;

	std::cout << "Original string array: ";
	::iter(strArray, strLen, ::printElement<std::string>);
	std::cout << std::endl;

	::iter(strArray, strLen, ::appendBang<std::string>);
	std::cout << "Modified string array: ";
	::iter(strArray, strLen, ::printElement<std::string>);
	std::cout << std::endl;

	std::cout << "Const string array: ";
	::iter(constStrArray, constStrLen, ::printElement<std::string>);
	std::cout << std::endl;

	return 0;
}