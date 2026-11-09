#include <deque>
#include <iostream>
#include <list>
#include <vector>
#include "easyfind.hpp"

int main() {
	int arr[] = {10, 20, 30, 40, 50};

	std::vector<int> vec(arr, arr + 5);
	std::list<int> lst(arr, arr + 5);
	std::deque<int> deq(arr, arr + 5);

	try {
		const std::vector<int>::iterator itVec = easyfind(vec, 30);
		std::cout << "Found in vector: " << *itVec << std::endl;
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		const std::list<int>::iterator itLst = easyfind(lst, 50);
		std::cout << "Found in list: " << *itLst << std::endl;
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		easyfind(deq, 99);
	} catch (const std::exception &e) {
		std::cout << "Expected exception while searching in deque: " << e.what() << std::endl;
	}

	try {
		const std::vector<int> constVec(arr, arr + 5);
		const std::vector<int>::const_iterator itConst = easyfind(constVec, 10);
		std::cout << "Found in const vector: " << *itConst << " at index " << (itConst - constVec.begin())
				<< std::endl;
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		std::vector<int>::iterator itMod = easyfind(vec, 20);
		*itMod = 21;
		std::cout << "Modified through returned iterator: vec[1] = " << vec[1] << std::endl;
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		std::vector<int> emptyVec;
		easyfind(emptyVec, 0);
	} catch (const std::exception &e) {
		std::cout << "Expected exception while searching in empty vector: " << e.what() << std::endl;
	}

	return 0;
}