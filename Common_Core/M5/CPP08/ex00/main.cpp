#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main() {
	int arr[] = {10, 20, 30, 40, 50};

	std::vector<int> vec(arr, arr + 5);
	std::list<int> lst(arr, arr + 5);
	std::deque<int> deq(arr, arr + 5);

	try {
		std::vector<int>::iterator itVec = easyfind(vec, 30);
		std::cout << "Found in vector: " << *itVec << std::endl;
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		std::list<int>::iterator itLst = easyfind(lst, 50);
		std::cout << "Found in list: " << *itLst << std::endl;
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		easyfind(deq, 99);
	} catch (const std::exception &e) {
		std::cout << "Deque search exception: " << e.what() << std::endl;
	}

	return 0;
}