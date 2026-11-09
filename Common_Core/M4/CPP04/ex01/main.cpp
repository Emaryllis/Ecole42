#include <iostream>
#include "Cat.hpp"
#include "Dog.hpp"

int main() {
	const int arraySize = 4;
	Animal *animals[arraySize];

	Dog *dog = new Dog();
	dog->getBrain()->setIdea(0, "Chase cat1");
	Dog *dogCopy = new Dog(*dog);
	dog->getBrain()->setIdea(0, "Chase cat2");
	std::cout << dog->getBrain()->getIdea(0) << std::endl;
	std::cout << dogCopy->getBrain()->getIdea(0) << std::endl;
	animals[0] = dog;
	animals[1] = dogCopy;

	Cat *cat = new Cat();
	cat->getBrain()->setIdea(0, "Chase dog1");
	Cat *catCopy = new Cat(*cat);
	cat->getBrain()->setIdea(0, "Chase dog2");
	std::cout << cat->getBrain()->getIdea(0) << std::endl;
	std::cout << catCopy->getBrain()->getIdea(0) << std::endl;
	animals[2] = cat;
	animals[3] = catCopy;

	for (int i = 0; i < arraySize; i++) {
		delete animals[i];
	}

	return 0;
}