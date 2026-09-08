#ifndef ARRAY_TPP
#define ARRAY_TPP

#include <iostream>

template <typename T>
Array<T>::Array() : _elements(NULL), _size(0) {
	std::cout << "Array Default Constructor called" << std::endl;
}

template <typename T>
Array<T>::Array(const unsigned int n) : _elements(new T[n]()), _size(n) {
	std::cout << "Array Parameterized Constructor called" << std::endl;
}

template <typename T>
Array<T>::Array(Array const &other) : _elements(NULL), _size(0) {
	std::cout << "Array Copy Constructor called" << std::endl;
	*this = other;
}

template <typename T>
Array<T> &Array<T>::operator=(Array const &other) {
	std::cout << "Array Copy Assignment Operator called" << std::endl;
	if (this != &other) {
		delete[] _elements;
		_size = other._size;
		if (_size > 0) {
			_elements = new T[_size]();
			for (unsigned int i = 0; i < _size; i++) {
				_elements[i] = other._elements[i];
			}
		} else {
			_elements = NULL;
		}
	}
	return *this;
}

template <typename T>
Array<T>::~Array() {
	std::cout << "Array Destructor called" << std::endl;
	delete[] _elements;
}

template <typename T>
T &Array<T>::operator[](unsigned int index) {
	if (index >= _size) {
		throw OutOfBoundsException();
	}
	return _elements[index];
}

template <typename T>
T const &Array<T>::operator[](unsigned int index) const {
	if (index >= _size) {
		throw OutOfBoundsException();
	}
	return _elements[index];
}

template <typename T>
unsigned int Array<T>::size() const {
	return _size;
}

template <typename T>
char const* Array<T>::OutOfBoundsException::what() const throw() {
	return "Index out of bounds";
}

#endif