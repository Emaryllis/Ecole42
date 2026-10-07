#ifndef MUTANT_STACK_TPP
#define MUTANT_STACK_TPP

#include <iostream>

template<typename T, typename Container>
MutantStack<T, Container>::MutantStack() : std::stack<T, Container>() {
	std::cout << "MutantStack default constructor called with size " << this->size() << std::endl;
}

template<typename T, typename Container>
MutantStack<T, Container>::MutantStack(const MutantStack &other) : std::stack<T, Container>(other) {
	std::cout << "MutantStack copy constructor called" << std::endl;
}

template<typename T, typename Container>
MutantStack<T, Container> &MutantStack<T, Container>::operator=(const MutantStack &other) {
	if (this != &other) {
		std::stack<T, Container>::operator=(other);
	}

	std::cout << "MutantStack copy assignment operator called" << std::endl;

	return *this;
}

template<typename T, typename Container>
MutantStack<T, Container>::~MutantStack() {
	std::cout << "MutantStack destructor called with size " << this->size() << std::endl;
}

template<typename T, typename Container>
typename MutantStack<T, Container>::iterator MutantStack<T, Container>::begin() {
	return this->c.begin();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::iterator MutantStack<T, Container>::end() {
	return this->c.end();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::const_iterator MutantStack<T, Container>::begin() const {
	return this->c.begin();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::const_iterator MutantStack<T, Container>::end() const {
	return this->c.end();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::reverse_iterator MutantStack<T, Container>::rbegin() {
	return this->c.rbegin();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::reverse_iterator MutantStack<T, Container>::rend() {
	return this->c.rend();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::const_reverse_iterator MutantStack<T, Container>::rbegin() const {
	return this->c.rbegin();
}

template<typename T, typename Container>
typename MutantStack<T, Container>::const_reverse_iterator MutantStack<T, Container>::rend() const {
	return this->c.rend();
}

#endif