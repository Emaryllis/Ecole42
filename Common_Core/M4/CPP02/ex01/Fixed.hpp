#ifndef FIXED_HPP
#define FIXED_HPP
#include <ostream>

class Fixed {
public:
	Fixed();
	Fixed(const Fixed &obj);
	explicit Fixed(int num);
	explicit Fixed(float num);
	~Fixed();
	Fixed &operator=(const Fixed &obj);
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
