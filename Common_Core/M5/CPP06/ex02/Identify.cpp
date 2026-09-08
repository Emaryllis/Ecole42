#include "Identify.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>

Base *generate(void) {
	const int randomChoice = std::rand() % 3;
	std::cout << "Generated number: " << randomChoice << std::endl;
	if (randomChoice == 0)
		return new A();
	if (randomChoice == 1)
		return new B();
	return new C();
}

void identify(Base *p) {
	if (dynamic_cast<A *>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown" << std::endl;
}

void identify(Base &p) {
	try {
		(void) dynamic_cast<A &>(p);
		std::cout << "A" << std::endl;
		return;
	} catch (...) {}
	try {
		(void) dynamic_cast<B &>(p);
		std::cout << "B" << std::endl;
		return;
	} catch (...) {}
	try {
		(void) dynamic_cast<C &>(p);
		std::cout << "C" << std::endl;
		return;
	} catch (...) {}
	std::cout << "Unknown" << std::endl;
}