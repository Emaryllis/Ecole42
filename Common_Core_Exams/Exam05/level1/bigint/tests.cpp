#include <cassert>
#include "bigint.hpp"

static void baseTest(const bigint &a, const bigint &b, const bigint &c) {
	assert(a == 42);
	assert(b == 21);
	assert(c == 1323);

	std::cout << "Base tests passed successfully!" << std::endl;
}

static void operatorTest(const bigint &a, const bigint &b, const bigint &c) {
	// Addition
	bigint tmp = a + b;
	assert(a + b == 63);
	assert(tmp == 63);
	assert(a + -b == 21);
	assert(-a + b == -21);
	assert(-a + -b == -63);
	assert(a + 21 == 63);

	// Subtraction
	tmp = a - b;
	assert(a - b == 21);
	assert(tmp == 21);
	assert(a - -b == 63);
	assert(-a - b == -63);
	assert(-a - -b == -21);
	assert(a - 21 == 21);

	// Multiplication
	tmp = a * b;
	assert(a * b == 882);
	assert(tmp == 882);
	assert(a * -b == -882);
	assert(-a * b == -882);
	assert(-a * -b == 882);
	assert(a * 21 == 882);

	// Division
	tmp = c / b;
	assert(c / b == 63);
	assert(tmp == 63);
	assert(c / -b == -63);
	assert(-c / b == -63);
	assert(-c / -b == 63);
	assert(c / 21 == 63);

	// Modulo
	tmp = c % b;
	assert(c % b == 0);
	assert(tmp == 0);
	assert(c % -b == 0);
	assert(-c % b == 0);
	assert(c % 21 == 0);

	tmp = c % a;
	assert(c % a == 21);
	assert(tmp == 21);
	assert(c % -a == 21);
	assert(-c % a == -21 || -c % a == 21);
	assert(c % 42 == 21);

	std::cout << "Operator tests passed successfully!" << std::endl;
}

static void compoundAssignmentTest(bigint a, bigint b, bigint c) {
	bigint tmp(a);
	// Addition
	a += b;
	tmp += 21;
	assert(a == tmp && tmp == 63);
	a -= b;
	tmp -= 21;
	assert(a == tmp && tmp == 42);

	// Subtraction
	tmp = b;
	b -= a;
	tmp -= 42;
	assert(b == tmp && tmp == -21);
	b -= -a;
	tmp -= -42;
	assert(b == tmp && tmp == 21);

	// Multiplication
	tmp = a;
	a *= -b;
	tmp *= -21;
	assert(a == tmp && tmp == -882);
	a *= b;
	tmp *= 21;
	assert(a == tmp && tmp == -18522);
	tmp *= 0;
	assert(tmp == 0);
	a *= -1;
	assert(a == 18522);

	// Division
	tmp = c;
	c /= b;
	tmp /= 21;
	assert(c == tmp && tmp == 63);
	c /= -b;
	tmp /= -21;
	assert(c == tmp && tmp == -3);
	tmp /= 3;
	assert(tmp == -1);

	// Modulo
	tmp = a;
	a %= c;
	tmp %= -1323;
	assert(a == tmp && tmp == 0);
	tmp = -b, b = -b;
	b %= bigint(10);
	tmp %= 10;
	assert(b == tmp && (tmp == 9 || tmp == -1));

	std::cout << "Compound assignment tests passed successfully!" << std::endl;
}

static void comparisonTest(const bigint &a, const bigint &b) {
	// Bigint vs Bigint
	assert(a > b);
	assert(b < a);
	assert(a >= b);
	assert(b <= a);
	assert(a == a && a == bigint(42));
	assert(a != b);

	// Bigint vs std::size_t / int primitives
	assert(a > 20);
	assert(a >= 42);
	assert(a < 100);
	assert(a <= 42);
	assert(b == 21);
	assert(a != 0);

	std::cout << "Comparison tests passed successfully!" << std::endl;
}

static void shiftTest(bigint b) {
	bigint tmp(b);

	// Left shift
	b = tmp << 2;
	tmp = tmp << bigint(2);
	assert(b == tmp && tmp == 2100);

	b = tmp << -2;
	tmp = tmp << bigint(-2);
	assert(b == tmp && tmp == 21);

	// Right shift
	b = tmp >> 1;
	tmp = tmp >> bigint(1);
	assert(b == tmp && tmp == 2);

	b = tmp >> -1;
	tmp = tmp >> bigint(-1);
	assert(b == tmp && tmp == 20);

	// Left shift
	b = 21;
	tmp = 21;
	b <<= 2;
	tmp <<= bigint(2);
	assert(b == tmp && tmp == 2100);

	b <<= -2;
	tmp <<= bigint(-2);
	assert(b == tmp && tmp == 21);

	// Right shift
	b >>= 1;
	tmp >>= bigint(1);
	assert(b == tmp && tmp == 2);

	b >>= -1;
	tmp >>= bigint(-1);
	assert(b == tmp && tmp == 20);

	std::cout << "Shift tests passed successfully!" << std::endl;
}

static void incrementTest(bigint a) {
	bigint tmp(a);

	// Pre-increment
	++a;
	++tmp;
	assert(a == 43 && tmp == 43);
	assert(a == tmp);

	// Pre-decrement
	--a;
	--tmp;
	assert(a == 42 && tmp == 42);
	assert(a == tmp);

	// Post-increment
	bigint old_a = a;
	bigint old_tmp = tmp;
	bigint res_a = a++;
	bigint res_tmp = tmp++;
	assert(res_a == old_a);
	assert(res_tmp == old_tmp);
	assert(a == 43 && tmp == 43);

	// Post-decrement
	old_a = a;
	old_tmp = tmp;
	res_a = a--;
	res_tmp = tmp--;
	assert(res_a == old_a);
	assert(res_tmp == old_tmp);
	assert(a == 42 && tmp == 42);

	std::cout << "Increment/Decrement tests passed successfully!" << std::endl;
}

static void edgeCaseTest() {
	bigint def;
	assert(def == 0);
	assert(static_cast<std::string>(def) == "0");

	// Negative zero protection
	bigint zero(0);
	bigint neg_zero = -zero;
	assert(static_cast<std::string>(zero) == "0");
	assert(static_cast<std::string>(neg_zero) == "0");
	assert(neg_zero == 0);

	assert(static_cast<std::string>(bigint(-42)) == "-42");
	assert(static_cast<std::string>(bigint(1323)) == "1323");

	// Self-assignment
	bigint x(42);
	x = x;
	assert(x == 42);
	x += x;
	assert(x == 84);

	std::cout << "Edge case tests passed successfully!" << std::endl;
}

int main() {
	const bigint a(42), b(21), c(1323);

	baseTest(a, b, c);
	operatorTest(a, b, c);
	compoundAssignmentTest(a, b, c);
	comparisonTest(a, b);
	shiftTest(b);
	incrementTest(a);
	edgeCaseTest();
	return 0;
}