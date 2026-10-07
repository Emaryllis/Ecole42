#ifndef EASY_FIND_HPP
#define EASY_FIND_HPP

#include <exception>

class NotFoundException : public std::exception {
public:
	virtual const char *what() const throw();
};

template<typename T>
typename T::iterator easyfind(T &container, int value);

#include "easyfind.tpp"

#endif