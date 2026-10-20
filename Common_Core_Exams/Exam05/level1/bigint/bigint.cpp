#include "bigint.hpp"

// =============================================================================
// Core Functions (Constructors, String Conversion, Base Assignments, Base Comp)
// =============================================================================

bigint::bigint() : negative(false) {
	_numArr.push_back(0);
}

bigint::bigint(const long long n) : negative(false) {
	unsigned long long magnitude = 0;
	if (n < 0)
		magnitude = static_cast<unsigned long long>(-(n + 1)) + 1;
	else
		magnitude = static_cast<unsigned long long>(n);
	negative = n < 0;

	if (magnitude == 0) {
		_numArr.push_back(0);
		negative = false;
		return;
	}
	while (magnitude > 0) {
		_numArr.push_front(static_cast<uint8_t>(magnitude % 10));
		magnitude /= 10;
	}
}

bigint::bigint(const bigint &n) : _numArr(n._numArr), negative(n.negative) {}

bigint::operator std::string() const {
	std::string ret;
	if (negative && !(_numArr.size() == 1 && _numArr.front() == 0))
		ret.push_back('-');
	const size_t len = this->_numArr.size();
	ret.reserve(ret.size() + len);
	for (size_t i = 0; i < _numArr.size(); i++)
		ret.push_back('0' + _numArr[i]);
	return ret;
}

bigint bigint::operator-() const {
	bigint tmp(*this);
	if (tmp._numArr.size() != 1 || tmp._numArr.front() != 0)
		tmp.negative = !tmp.negative;
	return tmp;
}

bigint &bigint::operator+=(const bigint &n) {
	if (n.negative) {
		bigint tmp = n;
		tmp.negative = false;
		return *this -= tmp;
	}
	if (negative) {
		negative = false;
		*this -= n;
		negative = !negative;
		if (_numArr.size() == 1 && _numArr.front() == 0)
			negative = false;
		return *this;
	}

	int carry = 0;
	std::deque<uint8_t>::const_reverse_iterator it1 = _numArr.rbegin();
	std::deque<uint8_t>::const_reverse_iterator it2 = n._numArr.rbegin();
	std::deque<uint8_t> result;

	while (it1 != _numArr.rend() || it2 != n._numArr.rend() || carry) {
		int num = carry;
		if (it1 != _numArr.rend())
			num += *it1++;
		if (it2 != n._numArr.rend())
			num += *it2++;
		carry = num / 10;
		result.push_front(static_cast<uint8_t>(num % 10));
	}
	_numArr = result;
	return *this;
}

bigint &bigint::operator-=(const bigint &n) {
	if (n.negative) {
		bigint tmp(n);
		tmp.negative = false;
		return *this += tmp;
	}
	if (negative) {
		negative = false;
		*this += n;
		negative = true;
		return *this;
	}
	if (*this < n) {
		bigint tmp = n;
		tmp -= *this;
		*this = tmp;
		this->negative = true;
		return *this;
	}

	int borrow = 0;
	std::deque<uint8_t>::const_reverse_iterator it1 = _numArr.rbegin();
	std::deque<uint8_t>::const_reverse_iterator it2 = n._numArr.rbegin();
	std::deque<uint8_t> result;

	while (it1 != _numArr.rend() || it2 != n._numArr.rend()) {
		int num = borrow;
		if (it1 != _numArr.rend())
			num += *it1++;
		if (it2 != n._numArr.rend())
			num -= *it2++;
		if (num < 0)
			num += 10;
		borrow = -(num < 0);
		result.push_front(static_cast<uint8_t>(num));
	}
	while (result.size() > 1 && result.front() == 0)
		result.pop_front();
	_numArr = result;
	if (_numArr.size() == 1 && _numArr.front() == 0)
		negative = false;
	return *this;
}

bigint &bigint::operator*=(const bigint &n) {
	std::size_t val = 0;
	for (std::deque<uint8_t>::const_iterator it = n._numArr.begin(); it != n._numArr.end(); ++it)
		val = val * 10 + *it;
	bool res = negative != n.negative;
	bigint original(*this);
	original.negative = false;
	_numArr.clear();
	_numArr.push_back(0);
	negative = false;
	for (std::size_t i = 0; i < val; ++i)
		*this += original;
	negative = _numArr.size() == 1 && _numArr.front() == 0 ? false : res;
	return *this;
}

bigint &bigint::operator/=(const bigint &n) {
	std::size_t val = 0;
	for (std::deque<uint8_t>::const_iterator it = n._numArr.begin(); it != n._numArr.end(); ++it)
		val = val * 10 + *it;
	if (val == 0) return *this;
	bool res_negative = negative != n.negative;
	std::size_t current = 0;
	std::deque<uint8_t> result;
	for (std::deque<uint8_t>::const_iterator it = _numArr.begin(); it != _numArr.end(); ++it) {
		current = current * 10 + *it;
		result.push_back(static_cast<uint8_t>(current / val));
		current %= val;
	}
	while (result.size() > 1 && result.front() == 0)
		result.pop_front();
	_numArr = result;
	negative = _numArr.size() == 1 && _numArr.front() == 0 ? false : res_negative;
	return *this;
}

bigint &bigint::operator<<=(const bigint &n) {
	if (n.negative) {
		bigint pos_n(n);
		pos_n.negative = false;
		return *this >>= pos_n;
	}
	std::size_t val = 0;
	for (std::deque<unsigned char>::const_iterator it = n._numArr.begin(); it != n._numArr.end(); ++it)
		val = val * 10 + *it;
	if (this->_numArr.size() == 1 && this->_numArr.front() == 0)
		return *this;
	for (std::size_t i = 0; i < val; ++i)
		this->_numArr.push_back(0);
	return *this;
}

bigint &bigint::operator>>=(const bigint &n) {
	if (n.negative) {
		bigint tmp(n);
		tmp.negative = false;
		return *this <<= tmp;
	}
	std::size_t val = 0;
	for (std::deque<unsigned char>::const_iterator it = n._numArr.begin(); it != n._numArr.end(); ++it)
		val = val * 10 + *it;
	for (std::size_t i = 0; i < val && !this->_numArr.empty(); ++i)
		this->_numArr.pop_back();
	if (this->_numArr.empty()) {
		this->_numArr.push_back(0);
		this->negative = false;
	}
	return *this;
}

bool bigint::operator>(const bigint &n) const {
	if (negative != n.negative)
		return !negative;
	bool res;
	if (_numArr.size() != n._numArr.size()) {
		res = _numArr.size() > n._numArr.size();
	} else {
		res = false;
		for (size_t i = 0; i < _numArr.size(); ++i) {
			if (_numArr[i] != n._numArr[i]) {
				res = _numArr[i] > n._numArr[i];
				break;
			}
		}
	}
	return negative ? !res : res;
}

bool bigint::operator==(const bigint &n) const {
	if (negative != n.negative) return false;
	if (_numArr.size() != n._numArr.size()) return false;
	for (size_t i = 0; i < n._numArr.size(); i++) {
		if (_numArr[i] != n._numArr[i])
			return false;
	}
	return true;
}

// =============================================================================
// Derived / Boilerplate Functions
// =============================================================================

bigint &bigint::operator%=(const bigint &n) {
	bigint q = *this;
	q /= n;
	q *= n;
	return *this -= q;
}

bigint &bigint::operator%=(const std::size_t n) {
	return *this %= bigint(n);
}

bigint &bigint::operator+=(const std::size_t n) {
	return *this += bigint(n);
}

bigint &bigint::operator*=(const std::size_t n) {
	return *this *= bigint(n);
}

bigint &bigint::operator/=(const std::size_t n) {
	return *this /= bigint(n);
}

bigint &bigint::operator<<=(const std::size_t n) {
	return *this <<= bigint(n);
}

bigint &bigint::operator>>=(const std::size_t n) {
	return *this >>= bigint(n);
}

bigint bigint::operator+(const std::size_t n) const {
	bigint tmp(*this);
	return tmp += n;
}

bigint bigint::operator-(const std::size_t n) const {
	bigint tmp(*this);
	return tmp -= n;
}

bigint bigint::operator*(const std::size_t n) const {
	bigint tmp(*this);
	return tmp *= n;
}

bigint bigint::operator/(const std::size_t n) const {
	bigint tmp(*this);
	return tmp /= n;
}

bigint bigint::operator%(std::size_t n) const {
	bigint tmp(*this);
	return tmp %= n;
}

bigint bigint::operator+(const bigint &n) const {
	bigint tmp(*this);
	return tmp += n;
}

bigint bigint::operator-(const bigint &n) const {
	bigint tmp(*this);
	return tmp -= n;
}

bigint bigint::operator*(const bigint &n) const {
	bigint tmp(*this);
	return tmp *= n;
}

bigint bigint::operator/(const bigint &n) const {
	bigint tmp(*this);
	return tmp /= n;
}

bigint bigint::operator%(const bigint &n) const {
	bigint tmp(*this);
	return tmp %= n;
}

bool bigint::operator<(const bigint &n) const {
	return !(*this > n || *this == n);
}

bool bigint::operator>=(const bigint &n) const {
	return *this > n || *this == n;
}

bool bigint::operator<=(const bigint &n) const {
	return *this < n || *this == n;
}

bool bigint::operator!=(const bigint &n) const {
	return !(*this == n);
}

bool bigint::operator>(const std::size_t n) const {
	return *this > bigint(n);
}

bool bigint::operator==(const std::size_t n) const {
	return *this == bigint(n);
}

bool bigint::operator<(const std::size_t n) const {
	return *this < bigint(n);
}

bool bigint::operator>=(const std::size_t n) const {
	return *this >= bigint(n);
}

bool bigint::operator<=(const std::size_t n) const {
	return *this <= bigint(n);
}

bool bigint::operator!=(const std::size_t n) const {
	return *this != bigint(n);
}

bigint &bigint::operator-=(const std::size_t n) {
	return *this -= bigint(n);
}

bigint &bigint::operator++() {
	*this += 1;
	return *this;
}

bigint bigint::operator++(int) {
	bigint tmp(*this);
	++*this;
	return tmp;
}

bigint &bigint::operator--() {
	*this -= 1;
	return *this;
}

bigint bigint::operator--(int) {
	bigint tmp(*this);
	--*this;
	return tmp;
}

bigint bigint::operator<<(const std::size_t n) const {
	bigint tmp(*this);
	return tmp <<= n;
}

bigint bigint::operator>>(const std::size_t n) const {
	bigint tmp(*this);
	return tmp >>= n;
}

bigint bigint::operator<<(const bigint &n) const {
	bigint tmp(*this);
	return tmp <<= n;
}

bigint bigint::operator>>(const bigint &n) const {
	bigint tmp(*this);
	return tmp >>= n;
}

bigint &bigint::operator=(const bigint &n) {
	if (this != &n) {
		this->_numArr = n._numArr;
		this->negative = n.negative;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &os, const bigint &n) {
	return os << static_cast<std::string>(n);
}