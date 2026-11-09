#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "MutantStack.hpp"

static void testSubject(std::vector<int> &out) {
	std::cout << "\n===== Subject test (MutantStack) =====" << std::endl;
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	out.push_back(mstack.top());
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	out.push_back(static_cast<int>(mstack.size()));
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite) {
		std::cout << *it << std::endl;
		out.push_back(*it);
		++it;
	}
	std::stack<int> s(mstack);
	std::cout << "std::stack copy size: " << s.size() << std::endl;
	out.push_back(static_cast<int>(s.size()));
}

static void testList(std::vector<int> &out) {
	std::cout << "\n===== Same test with std::list (expected output) =====" << std::endl;
	std::list<int> lst;
	lst.push_back(5);
	lst.push_back(17);
	std::cout << lst.back() << std::endl;
	out.push_back(lst.back());
	lst.pop_back();
	std::cout << lst.size() << std::endl;
	out.push_back(static_cast<int>(lst.size()));
	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	//[...]
	lst.push_back(0);
	std::list<int>::iterator it = lst.begin();
	std::list<int>::iterator ite = lst.end();
	++it;
	--it;
	while (it != ite) {
		std::cout << *it << std::endl;
		out.push_back(*it);
		++it;
	}
	std::list<int> l(lst);
	std::cout << "std::list copy size: " << l.size() << std::endl;
	out.push_back(static_cast<int>(l.size()));
}

static void testReverseAndConst() {
	std::cout << "\n===== Reverse iteration =====" << std::endl;
	MutantStack<std::string> words;
	words.push("first");
	words.push("second");
	words.push("third");
	for (MutantStack<std::string>::reverse_iterator rit = words.rbegin(); rit != words.rend(); ++rit) {
		std::cout << *rit << ' ';
	}
	std::cout << "(top: " << words.top() << ")" << std::endl;

	std::cout << "\n===== Const iteration =====" << std::endl;
	const MutantStack<std::string> constWords(words);
	for (MutantStack<std::string>::const_iterator cit = constWords.begin(); cit != constWords.end(); ++cit) {
		std::cout << *cit << ' ';
	}
	std::cout << std::endl;
	for (MutantStack<std::string>::const_reverse_iterator crit = constWords.rbegin(); crit != constWords.rend();
	     ++crit) {
		std::cout << *crit << ' ';
	}
	std::cout << std::endl;
}

static void testCopyAndModify() {
	std::cout << "\n===== Copy, assignment and modification through iterator =====" << std::endl;
	MutantStack<int> original;
	for (int i = 1; i <= 3; ++i) {
		original.push(i * 10);
	}
	MutantStack<int> assigned;
	assigned = original;
	for (MutantStack<int>::iterator it = assigned.begin(); it != assigned.end(); ++it) {
		*it += 1;
	}
	std::cout << "original: ";
	for (MutantStack<int>::iterator it = original.begin(); it != original.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << "| assigned: ";
	for (MutantStack<int>::iterator it = assigned.begin(); it != assigned.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
}

static void testOtherContainer() {
	std::cout << "\n===== MutantStack with std::vector as underlying container =====" << std::endl;
	MutantStack<int, std::vector<int> > vstack;
	vstack.push(1);
	vstack.push(2);
	vstack.push(3);
	for (MutantStack<int, std::vector<int> >::iterator it = vstack.begin(); it != vstack.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << "(top: " << vstack.top() << ")" << std::endl;
}

int main() {
	std::vector<int> stackResult;
	std::vector<int> listResult;
	testSubject(stackResult);
	testList(listResult);
	std::cout << "\n===== MutantStack vs std::list =====" << std::endl;
	std::cout << (stackResult == listResult ? "OK: outputs match" : "KO: outputs differ") << std::endl;
	testReverseAndConst();
	testCopyAndModify();
	testOtherContainer();
	return 0;
}