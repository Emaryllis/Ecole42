#include <cassert>
#include <iostream>
#include <list>
#include <sstream>
#include "MutantStack.hpp"

long getTestMutantStack() {
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);

	std::ostringstream oss;
	oss << mstack.top() << "\n";
	mstack.pop();
	oss << mstack.size() << "\n";
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);

	long hash = 0;
	for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
		hash = hash * 31 + *it;
	}
	return hash;
}

long getTestList() {
	std::list<int> lst;
	lst.push_back(5);
	lst.push_back(17);

	std::ostringstream oss;
	oss << lst.back() << "\n";
	lst.pop_back();
	oss << lst.size() << "\n";
	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	lst.push_back(0);

	int hash = 0;
	for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
		hash = hash * 31 + *it;
	}
	return hash;
}

int main() {
	assert(getTestMutantStack() == getTestList());
	std::cout << "Hash matches with list implementation!" << std::endl;

	std::cout << "All tests passed!" << std::endl;
	return 0;
}