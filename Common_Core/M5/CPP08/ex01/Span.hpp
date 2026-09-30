#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <exception>

class Span {
public:
	Span();
	Span(unsigned int N);
	Span(const Span &other);
	Span &operator=(const Span &other);
	~Span();

	void addNumber(int number);

	template<typename InputIterator>
	void addRange(InputIterator begin, InputIterator end) {
		if (_numbers.size() + std::distance(begin, end) > _maxSize) {
			throw FullSpanException();
		}
		_numbers.insert(_numbers.end(), begin, end);
	}

	int shortestSpan() const;
	int longestSpan() const;

	class FullSpanException : public std::exception {
	public:
		virtual const char *what() const throw() {
			return "Span is full";
		}
	};

	class NoSpanException : public std::exception {
	public:
		virtual const char *what() const throw() {
			return "Not enough elements to calculate span";
		}
	};

protected:

private:
	unsigned int _maxSize;
	std::vector<int> _numbers;
};

#endif