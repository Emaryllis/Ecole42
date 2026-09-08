#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>

template <typename T>
class Array {
public:
	Array();
	Array(unsigned int n);
	Array(Array const &other);
	Array &operator=(Array const &other);
	~Array();

	T &operator[](unsigned int index);
	T const &operator[](unsigned int index) const;

	unsigned int size() const;

	class OutOfBoundsException : public std::exception {
	public:
		virtual char const* what() const throw();
	};

private:
	T* _elements;
	unsigned int _size;
};

#include "Array.tpp"

#endif