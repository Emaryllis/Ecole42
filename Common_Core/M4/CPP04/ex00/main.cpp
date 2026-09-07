#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

#include <iostream>

int main() {
	Animal a1;
	Animal a2("Animal2");
	Cat c1;
	Cat c2("Cat2");
	Dog d1;
	Dog d2("Dog2");
	std::cout << a2.getType() << " " << std::endl;
	std::cout << c2.getType() << " " << std::endl;
	std::cout << d2.getType() << " " << std::endl;
	a2.makeSound();
	c2.makeSound();
	d2.makeSound();

	WrongAnimal wa1;
	WrongAnimal wa2("WrongAnimal2");
	WrongCat wc1;
	WrongCat wc2("WrongCat2");
	std::cout << wa2.getType() << " " << std::endl;
	std::cout << wc2.getType() << " " << std::endl;
	wa2.makeSound();
	wc2.makeSound();

    return 0;
}
