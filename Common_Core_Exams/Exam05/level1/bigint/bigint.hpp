#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <climits>
#include <deque>
#include <iostream>
#include <stdint.h> // NOLINT(*-deprecated-headers): Not replacing with cstdint for C++98 compatibility
#include <string>

class bigint {
public:
	// =============================================================================
	// Core Functions (Constructors, String Conversion, Base Assignments, Base Comp)
	// =============================================================================
	bigint();
	bigint(long long n);
	bigint(const bigint &n);
	operator std::string() const;
	bigint operator-() const;

	bigint &operator+=(const bigint &n);
	bigint &operator-=(const bigint &n);
	bigint &operator*=(const bigint &n);
	bigint &operator/=(const bigint &n);
	bigint &operator<<=(const bigint &n);
	bigint &operator>>=(const bigint &n);

	bool operator>(const bigint &n) const;
	bool operator==(const bigint &n) const;

	// =============================================================================
	// Derived / Boilerplate Functions
	// =============================================================================
	bigint &operator%=(const bigint &n);
	bigint &operator%=(std::size_t n);
	bigint &operator+=(std::size_t n);
	bigint &operator*=(std::size_t n);
	bigint &operator/=(std::size_t n);
	bigint &operator<<=(std::size_t n);
	bigint &operator>>=(std::size_t n);

	bigint operator+(std::size_t n) const;
	bigint operator-(std::size_t n) const;
	bigint operator*(std::size_t n) const;
	bigint operator/(std::size_t n) const;
	bigint operator%(std::size_t n) const;
	bigint operator+(const bigint &n) const;
	bigint operator-(const bigint &n) const;
	bigint operator*(const bigint &n) const;
	bigint operator/(const bigint &n) const;
	bigint operator%(const bigint &n) const;

	bool operator<(const bigint &n) const;
	bool operator>=(const bigint &n) const;
	bool operator<=(const bigint &n) const;
	bool operator!=(const bigint &n) const;
	bool operator>(std::size_t n) const;
	bool operator==(std::size_t n) const;
	bool operator<(std::size_t n) const;
	bool operator>=(std::size_t n) const;
	bool operator<=(std::size_t n) const;
	bool operator!=(std::size_t n) const;

	bigint &operator-=(std::size_t n);
	bigint &operator++();
	bigint operator++(int);
	bigint &operator--();
	bigint operator--(int);
	bigint operator<<(std::size_t n) const;
	bigint operator>>(std::size_t n) const;
	bigint operator<<(const bigint &n) const;
	bigint operator>>(const bigint &n) const;
	bigint &operator=(const bigint &n);

private:
	std::deque<uint8_t> _numArr;
	bool negative;
};

std::ostream &operator<<(std::ostream &os, const bigint &n);

#endif