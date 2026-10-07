#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <exception>
#include <algorithm>


class Span {
public:
	Span(unsigned int n);
	Span(const Span &other);
	Span &operator=(const Span &rhs);
	~Span();

	void addNumber(int num);
	int shortestSpan() const;
	int longestSpan() const;

	template<typename Iterator>
	void addNumbers(Iterator begin, Iterator end);

	class SpanException : public std::exception {
	public:
		SpanException(const char *msg) throw();
		virtual const char *what() const throw();

	private:
		const char *_msg;
	};

private:
	Span();
	unsigned int _maxSize;
	std::vector<int> _numbers;
};

#include "Span.tpp"

#endif