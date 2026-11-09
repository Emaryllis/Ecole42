#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include "Array.hpp"

#define MAX_VAL 750

struct Bomb {
	int v;
	Bomb(): v(0) {}

	Bomb &operator=(Bomb const &o) {
		if (o.v == 2) throw std::runtime_error("Bomb copy failed");
		v = o.v;
		return *this;
	}
};

static int testOriginalMain() {
	Array<int> numbers(MAX_VAL);
	int *mirror = new int[MAX_VAL];
	srand(time(NULL));
	for (int i = 0; i < MAX_VAL; i++) {
		const int value = rand();
		numbers[i] = value;
		mirror[i] = value;
	}
	//SCOPE
	{
		Array<int> tmp = numbers;
		Array<int> test(tmp);
	}

	for (int i = 0; i < MAX_VAL; i++) {
		if (mirror[i] != numbers[i]) {
			std::cerr << "didn't save the same value!!" << std::endl;
			return 1;
		}
	}
	try {
		numbers[-2] = 0;
	} catch (const std::exception &e) {
		std::cerr << e.what() << '\n';
	}
	try {
		numbers[MAX_VAL] = 0;
	} catch (const std::exception &e) {
		std::cerr << e.what() << '\n';
	}

	for (int i = 0; i < MAX_VAL; i++) {
		numbers[i] = rand();
	}
	delete [] mirror; //
	std::cout << "Subject test passed" << std::endl;
	return 0;
}

static void testEmpty() {
	std::cout << "\n===== Empty array =====" << std::endl;
	Array<int> empty;
	std::cout << "Size: " << empty.size() << std::endl;
	try {
		empty[0] = 42;
	} catch (const std::exception &e) {
		std::cout << "Expected exception: " << e.what() << std::endl;
	}

	Array<int> zero(0);
	std::cout << "Array(0) size: " << zero.size() << std::endl;
}

static void testDefaultInit() {
	std::cout << "\n===== Default initialisation =====" << std::endl;
	Array<int> ints(5);
	std::cout << "Array<int>(5): ";
	for (unsigned int i = 0; i < ints.size(); i++) {
		std::cout << ints[i] << ' ';
	}
	std::cout << std::endl;
}

static void testDeepCopy() {
	std::cout << "\n===== Deep copy (copy constructor) =====" << std::endl;
	Array<int> original(3);
	for (unsigned int i = 0; i < original.size(); i++) {
		original[i] = i * 10;
	}
	Array<int> copy(original);
	copy[0] = 999;
	std::cout << "original[0] = " << original[0] << ", copy[0] = " << copy[0] << std::endl;
	std::cout << ((original[0] == 0 && copy.size() == original.size()) ? "OK: deep copy" : "KO: shallow copy")
			<< std::endl;

	std::cout << "\n===== Deep copy (assignment operator) =====" << std::endl;
	Array<std::string> a(2);
	a[0] = "hello";
	a[1] = "world";
	Array<std::string> b(5);
	b = a;
	b[1] = "changed";
	std::cout << "a[1] = " << a[1] << ", b[1] = " << b[1] << ", b.size() = " << b.size() << std::endl;
	std::cout << ((a[1] == "world" && b.size() == 2) ? "OK: deep copy" : "KO: shallow copy") << std::endl;

	std::cout << "\n===== Self assignment =====" << std::endl;
	Array<std::string> &ref = a;
	a = ref;
	std::cout << "a[0] = " << a[0] << ", a[1] = " << a[1] << std::endl;
}

static void testConst() {
	std::cout << "\n===== Const array =====" << std::endl;
	Array<int> source(3);
	source[0] = 1;
	source[1] = 2;
	source[2] = 3;
	const Array<int> constArray(source);
	for (unsigned int i = 0; i < constArray.size(); i++) {
		std::cout << constArray[i] << ' ';
	}
	std::cout << std::endl;
	try {
		std::cout << constArray[3] << std::endl;
	} catch (const std::exception &e) {
		std::cout << "Expected exception: " << e.what() << std::endl;
	}
}

static void testThrowingCopy() {
	std::cout << "\n===== Throwing element copy (check with valgrind) =====" << std::endl;
	Array<Bomb> src(3);
	src[2].v = 2;
	try {
		Array<Bomb> copy(src);
	} catch (const std::exception &e) {
		std::cout << "Expected exception: " << e.what() << std::endl;
	}
	Array<Bomb> dst(1);
	dst[0].v = 7;
	try {
		dst = src;
	} catch (const std::exception &e) {
		std::cout << "Expected exception: " << e.what() << std::endl;
	}
	std::cout << "dst unchanged: size " << dst.size() << ", dst[0] = " << dst[0].v << std::endl;
}

int main() {
	if (testOriginalMain() == 1)
		return 1;
	testEmpty();
	testDefaultInit();
	testDeepCopy();
	testConst();
	testThrowingCopy();
	return 0;
}