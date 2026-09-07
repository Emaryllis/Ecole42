#include "Cat.hpp"
#include "Dog.hpp"
#include <iostream>
int main() {
	const int arraySize = 4;
	Animal* animals[arraySize];

	animals[0] = new Dog();
	static_cast<Dog*>(animals[0])->getBrain()->setIdea(0, "Chase cat1");
	animals[1] = new Dog(*static_cast<Dog*>(animals[0]));
	static_cast<Dog*>(animals[0])->getBrain()->setIdea(0, "Chase cat2");
	std::cout << static_cast<Dog*>(animals[0])->getBrain()->getIdea(0) << std::endl;
	std::cout << static_cast<Dog*>(animals[1])->getBrain()->getIdea(0) << std::endl;

	animals[2] = new Cat();
	static_cast<Cat*>(animals[2])->getBrain()->setIdea(0, "Chase dog1");
	animals[3] = new Cat(*static_cast<Cat*>(animals[2]));
	static_cast<Cat*>(animals[2])->getBrain()->setIdea(0, "Chase dog2");
	std::cout << static_cast<Cat*>(animals[2])->getBrain()->getIdea(0) << std::endl;
	std::cout << static_cast<Cat*>(animals[3])->getBrain()->getIdea(0) << std::endl;

	for (int i = 0; i < arraySize; i++) {
		delete animals[i];
	}

	return 0;
}
