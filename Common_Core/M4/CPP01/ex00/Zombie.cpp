#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(const std::string &name) : name(name) {
}

void Zombie::announce() const {
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

Zombie::~Zombie() {
	std::cout << name << " has been destroyed." << std::endl;
}
