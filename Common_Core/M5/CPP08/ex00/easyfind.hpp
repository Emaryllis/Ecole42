#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <exception>

class NotFoundException : public std::exception {
public:
	virtual const char *what() const throw() {
		return "Element not found in container";
	}
};

template<typename T>
typename T::iterator easyfind(T &container, int value);

#include "easyfind.tpp"

#endif