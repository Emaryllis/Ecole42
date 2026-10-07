#ifndef EASY_FIND_TPP
#define EASY_FIND_TPP

#include <algorithm>

inline const char *NotFoundException::what() const throw() {
	return "Element not found in container";
}

template<typename T>
typename T::iterator easyfind(T &container, int value) {
	typename T::iterator it = std::find(container.begin(), container.end(), value);
	if (it == container.end()) {
		throw NotFoundException();
	}
	return it;
}

#endif