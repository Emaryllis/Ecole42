#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed {
public:
	Fixed();
	Fixed(const Fixed &obj);
	~Fixed();
	Fixed &operator=(const Fixed &obj);
	int getRawBits() const;
	void setRawBits(int raw);

private:
	int fixedPoint;
	static const int fracBits;
};

#endif
