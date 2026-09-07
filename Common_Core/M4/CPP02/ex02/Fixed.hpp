#ifndef FIXED_HPP
#define FIXED_HPP
#include <ostream>

class Fixed {
public:
	Fixed();
	~Fixed();
	Fixed(const Fixed &obj);
	explicit Fixed(int num);
	explicit Fixed(float num);

	bool operator>(const Fixed &other) const;
	bool operator<(const Fixed &other) const;
	bool operator>=(const Fixed &other) const;
	bool operator<=(const Fixed &other) const;
	bool operator==(const Fixed &other) const;
	bool operator!=(const Fixed &other) const;

	Fixed &operator=(const Fixed &obj);
	Fixed operator*(const Fixed &other) const;
	Fixed operator/(const Fixed &other) const;
	Fixed operator+(const Fixed &other) const;
	Fixed operator-(const Fixed &other) const;
	Fixed operator++(int);
	Fixed operator++();
	Fixed operator--(int);
	Fixed operator--();

	static Fixed &max(Fixed &a, Fixed &b);
	static const Fixed &max(const Fixed &a, const Fixed &b);
	static Fixed &min(Fixed &a, Fixed &b);
	static const Fixed &min(const Fixed &a, const Fixed &b);

	int getRawBits() const;
	void setRawBits(int raw);
	float toFloat() const;
	int toInt() const;

private:
	int fixedPoint;
	static const int fracBits;
};

std::ostream &operator <<(std::ostream &out, const Fixed &obj);

#endif
