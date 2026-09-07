#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public AAnimal {
public:
	Dog();
	Dog(const std::string& type);
	Dog(const Dog& other);
	Dog& operator=(const Dog& other);
	Brain *getBrain() const;
	~Dog();

	virtual void makeSound() const;
private:
	Brain* brain;
};

#endif
